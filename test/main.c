#include <CoreLib.h>
#include <unistd.h>

void test_list(void);
void test_string_list(void);
void test_string(void);
void test_logger(void);
void test_configuration(void);

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
            test_configuration();
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
            test_logger();
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
            test_string();
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

    str_list_lock_iterator(mylist);

    item = str_list_get_first(mylist);

    while(item)
    {
        printf("%s\n", (char*)item);
        item = str_list_get_next(mylist);
    }

    str_list_unlock_iterator(mylist);

    str_list_clear(mylist);
    str_list_free(mylist);
}

void test_string(void)
{
    char* str = "aaxxbbxxccxxddxxeexx";

    long num_sub_strs = 0;
    char** sub_str_list = NULL;
    sub_str_list = strsplitsubstr(str, "xx", &num_sub_strs);

    for(int index = 0; sub_str_list[index] != 0; index++)
    {
        char* sub_str = NULL;
        sub_str = sub_str_list[index];
        printf("%s\n", sub_str);
    }

    strfreelist(sub_str_list, num_sub_strs);

    char process_name[64] = {0};
    char buffer[1025] = {0};
    pid_t proc_id = getpid();
    string_list_t* cmd_args = NULL;
    string_list_t* dir_tokens = NULL;

    sprintf(buffer, "/proc/%d/cmdline", proc_id);

    FILE* fp = fopen(buffer, "r");

    if(fp)
    {
        memset(buffer, 0, 1025);

        if(fgets(buffer, 1024, fp))
        {
            cmd_args = str_list_allocate_from_string(cmd_args, buffer, " ");

            if(cmd_args && str_list_item_count(cmd_args) > 0)
            {
                str_list_allocate_from_string(dir_tokens, str_list_get_first(cmd_args), "/");

                if(dir_tokens && str_list_item_count(dir_tokens) > 0)
                {
                    strcpy(process_name, str_list_get_last(dir_tokens));
                }
            }
            else
            {
                dir_tokens = str_list_allocate_from_string(dir_tokens, buffer, "/");

                if(dir_tokens && str_list_item_count(dir_tokens) > 0)
                {
                    strcpy(process_name, str_list_get_last(dir_tokens));
                }
            }
        }

        fclose(fp);
    }

    if(cmd_args)
    {
        str_list_clear(cmd_args);
        str_list_free(cmd_args);
    }

    if(dir_tokens)
    {
        str_list_clear(dir_tokens);
        str_list_free(dir_tokens);
    }
}

void test_logger(void)
{
    logger_t* logger = logger_allocate_default();

    WriteInformation(logger, "test");

    logger_release(logger);
}

void test_configuration(void)
{
    configuration_t* conf = configuration_allocate_default();

    char** sections = configuration_get_all_sections(conf);

    for(int sindex = 0; sections[sindex] != 0; sindex++)
    {
        char* sec_str = NULL;
        sec_str = sections[sindex];
        printf("Section %s\n", sec_str);

        char** keys = configuration_get_all_keys(conf, sections[sindex]);

        for(int kindex = 0; keys[kindex] != 0; kindex++)
        {
            char* key_str = NULL;
            key_str = keys[kindex];
            printf("Key %s Value %s\n", key_str, configuration_get_value_as_string(conf, sec_str, key_str));
        }

        strfreelist(keys, 0);
    }

    strfreelist(sections, 0);

    configuration_release(conf);
}
