# Epoll原理

## epoll主要函数
1. epoll_create(), 创建eventpoll
2. epoll_ctl(), 操作eventpoll
3. epoll_wait(), 返回eventpoll中活跃事件

## 核心数据结构
1. eventpoll : {rbr, rdlist, ... }, 即包含两个epitem容器，rbr指向红黑树根节点，rdlist指向双链表头节点
2. epitem : {rbn, rdlink, event, ...}, 主要包含红黑树节点rbn，双链表节点rdlink，即红黑树和双链表存放的节点都是epitem对象

eventpoll
---------------------------------------------------------------------
struct eventpoll
{
	spin_lock_t				lock;
	struct mutex 			mtx; 				//互斥锁，防止使用时被删除
	wait_queue_head_t 		wq;
	wait_queue_head_t		poll_wait
	struct list_head		rdlist;				//双向链表头节点
	struct rb_root 			rbr;				//红黑树根节点		
	...
}
----------------------------------------------------------------------

epitem
----------------------------------------------------------------------
struct epitem
{
	struct rb_node 			rbn;				//红黑树节点
	struct list_head 		rdlink;				//就绪链表
	struct eventpoll 		* ep; 				//属于哪个eventpoll
	struct epoll_event   	event;				//注册的感兴趣事件epoll_event
	...
}
----------------------------------------------------------------------

## 关键函数
1. epoll_create()
   - 创建eventpoll对象，包含一棵空红黑树和一个空双向链表
2. epoll_ctl()
   - 封装epitem对象，进行相关的操作：epitem插入红黑树、更新红黑树中的epitem、删除红黑树中的epitem
3. epoll_wait()
   - 从双向链表中去取相关事件通知。如果有节点，则取出节点中的事件填充到用户传入的指针指向的内存中，如果没有，
   则在while循环中等待一定时间，直到有事件被触发后操作系统会将epitem插入到双向链表上(epoll_event_callback函数调用)，使rdnum > 0 时，跳出
   while循环，取双向链表取数据
4. epoll_event_callback()调用
   - 客户端connect()连入，服务器处于SYN_RCVD状态
   - 三路握手完成，服务器处于ESTABLISHED状态
   - 客户端close()断开连接，服务器处于FIN_WAIT_1和FIN_WAIT_2状态时
   - 客户端send/write数据，服务器可读时
   - 服务器可以发送数据
   - 作用：将eventpoll所指向的红黑树节点插入到双向链表中

##总结
- epoll底层有两个关键数据结构：epitem、eventpoll，其中eventpoll中有指向红黑树根节点的rbr，指向双向链表头节点的rdlist，epitem可存储到红黑树中
  和双向链表，epitem包含用户注册的事件
- 调用epoll_create()时，创建eventpoll对象（包含一个红黑树和一个双向链表）
- 调用epoll_ctl()时，在红黑树上操作epitem对象（增删改查）
- 当事件被触发时，系统调用epoll_event_callback函数，将包含该事件的epitem添加到双向链表中
- 调用epoll_wait()时，从eventpoll对象中的双链表取epitem

#LT与ET模式区别
 - 在ET模式下，epitem从rdlist取出后不会再放回去，除非fd再次触发，epoll_event_callback被调用
 - 在LT模式下，epitem从rdlist取出后会再次放回去，下一次epoll_wait立即返回该epitem，如果该fd没有数据，epoll_wait返回0，空转一次

