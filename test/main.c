#include <CoreLib.h>

void test_list(void);
void test_string_list(void);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage : coretest <option>\nOptions are b, f, c, d, t, y, e, k, l, g, q, r, i, s, x, n, v\n");
        return -1;
    }

    switch (argv[1][0])
    {
        case 'b':
        {
            //Base64
            break;
        }
        case 'f':
        {
            //Buffer
            break;
        }
        case 'c':
        {
            //Configuration
            break;
        }
        case 'd':
        {
            //Dictionary
            break;
        }
        case 't':
        {
            //DateTime
            break;
        }
        case 'y':
        {
            //Directory
            break;
        }
        case 'e':
        {
            //Environmemt
            break;
        }
        case 'k':
        {
            //KeyValue
            break;
        }
        case 'l':
        {
            //List
            test_list();
            break;
        }
        case 'g':
        {
            //Logger
            break;
        }
        case 'q':
        {
            //Queue
            break;
        }
        case 'r':
        {
            //Responder
            break;
        }
        case 'i':
        {
            //SignalHandler
            break;
        }
        case 's':
        {
            //Stack
            break;
        }
        case 'x':
        {
            //StringEx
            break;
        }
        case 'n':
        {
            //StringList
            test_string_list();
            break;
        }
        case 'v':
        {
            //Variant
            break;
        }
        default:
        {
            break;
        }
    }

    return 0;
}

void test_list(void)
{
    list_t* mylist = NULL;

    mylist = list_allocate(mylist);

    list_add_to_tail(mylist, "Hello", strlen("Hello"));
    list_add_to_tail(mylist, "World", strlen("World"));
    list_add_to_tail(mylist, "Linux", strlen("Linux"));

    void* item = NULL;

    list_lock_iterator(mylist);

    item = list_get_first(mylist);

    while(item)
    {
        printf("%s\n", (char*)item);
        item = list_get_next(mylist);
    }

    list_unlock_iterator(mylist);

    list_clear(mylist);
    list_free(mylist);
}

void test_string_list(void)
{
    string_list_t* mylist = NULL;

    mylist = str_list_allocate(mylist);

    str_list_add(mylist, "Hello");
    str_list_add(mylist, "World");
    str_list_add(mylist, "Linux");

    char* item = NULL;

    //str_list_lock_iterator(mylist);

    item = str_list_get_first(mylist);

    while(item)
    {
        printf("%s\n", (char*)item);
        item = str_list_get_next(mylist);
    }

    //str_list_unlock_iterator(mylist);

    str_list_clear(mylist);
    str_list_free(mylist);
}
