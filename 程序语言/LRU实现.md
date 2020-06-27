# LRU算法实现 #
    struct Node{
    	int key, value;
    	Node *prev, *next;
    	Node():key(0), value(0), prev(nullptr), next(nullptr) {}
    	Node(int k, int v):key(k), value(v), prev(nullptr), next(nullptr) {}
	};
	class LRUCache {
		private:
    	int size, capa;
    	Node *head, *tail;
    	unordered_map<int, Node*> cache;
	public:
    	LRUCache(int capacity) {
        	size = 0;
        	capa = capacity;
        	head = new Node();
        	tail = new Node();
        	head->next = tail;
        	tail->prev = head;
    	}
    
    	int get(int key) {
        	if(!cache.count(key))
            	return -1;
        	Node *node = cache[key];
        	moveToHead(node);
        	return node->value;
    	}
    
    	void put(int key, int value) {
        	if(!cache.count(key))
        	{
            	Node *node = new Node(key, value);
            	cache[key] = node;
            	addToHead(node);
            	++size;
            	if(size > capa)
            	{
                	Node *rmnode = removeTail();
                	cache.erase(rmnode->key);
                	delete rmnode;
                	--size;
            	}
        	}
        	else
        	{
            	Node *node = cache[key];
            	node->value = value;
            	moveToHead(node);
        	}
    	}

    	void addToHead(Node *node)
    	{
        	node->prev = head;
        	node->next = head->next;
        	head->next->prev = node;
        	head->next = node;
    	}

    	void moveToHead(Node *node)
    	{
        	removeNode(node);
        	addToHead(node);
    	}

    	void removeNode(Node *node)
    	{
       		node->prev->next = node->next;
        	node->next->prev = node->prev;
    	}

    	Node* removeTail()
    	{
        	Node *node = tail->prev;
        	removeNode(node);
        	return node;
    	}
	};