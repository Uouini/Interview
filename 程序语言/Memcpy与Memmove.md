##### memcpy与memmove

memcpy直接正向拷贝，如果源数据地址与目的数据地址重叠，会出错
memmove分情况拷贝，如果源数据地址大于目的数据地址，正向拷贝，否则反向拷贝

#####memcpy实现

```c
void memcpy(void *dst, const void *src, size_t count)
{
    void *ret = dst;
    while(count--)
    {
        *(char*)dst = *(char*)src;
        dst = (char *)dst + 1;
        src = (char *)src + 1;
    }
    return ret;
}
```

##### memmove实现

```c
void memmove(void *dst, const void *src, size_t count)
{
    if(dst <= src || (char *)dst >= (char *)src + count)
    {
        while(count--)
        {
            *(char *)dst = *(char *)src;
            dst = (char *)dst + 1;
            src = (char *)src + 1;
        }
    }
    else
    {
        dst = (char *)dst + count - 1;
        src = (char *)src + count - 1;
        while(count--)
        {
            *(char *)dst = *(char *)src;
            dst = (char *)dst - 1;
            src = (char *)src - 1;
        }
    }
    return ret;
}
```

