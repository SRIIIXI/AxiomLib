#include <CoreLib.h>

int main(int argc, char* argv[])
{
    list_t* mylist = NULL;

    mylist = list_allocate(mylist);

    list_add_to_tail(mylist, "Hello", strlen("Hello"));
    list_add_to_tail(mylist, "World", strlen("World"));
    list_add_to_tail(mylist, "Linux", strlen("Linux"));

    void* item = NULL;

    item = list_get_first(mylist);

    while(item)
    {
        printf("%s\n", (char*)item);
        item = list_get_next(mylist);
    }

    list_clear(mylist);
    list_free(mylist);

    return 0;
}
