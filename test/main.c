#include <CoreLib.h>
#include <stdio.h>

void test_list(void);
void test_string_list(void);
void test_string(void);
void test_logger(void);
void test_configuration(void);
void test_dictionary(void);
void test_base64(void);
void test_email(void);
void test_queue(void);

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
            test_base64();
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
            test_dictionary();
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
            test_queue();
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
        case 'm':
        {
            //Email
            test_email();
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

    char** sub_str_list = NULL;
    sub_str_list = strsplitsubstr(str, "xx");

    for(int index = 0; sub_str_list[index] != 0; index++)
    {
        char* sub_str = NULL;
        sub_str = sub_str_list[index];
        printf("%s\n", sub_str);
    }

    strfreelist(sub_str_list);

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

        strfreelist(keys);
    }

    strfreelist(sections);

    configuration_release(conf);
}

void test_dictionary(void)
{
    dictionary_t* dict = dictionary_allocate();

    dictionary_set_value(dict, "123", strlen("123"), "ABCDEFGHIJKLMN", strlen("ABCDEFGHIJKLMN"));
    dictionary_set_value(dict, "ABC", strlen("ABC"), "0123456789", strlen("0123456789"));

    char* val1 = (char*)dictionary_get_value(dict, "123", strlen("123"));
    char* val2 = (char*)dictionary_get_value(dict, "ABC", strlen("ABC"));

    dictionary_set_value(dict, "123", strlen("123"), "opqrstuvwxyz", strlen("opqrstuvwxyz"));
    char* val3 = (char*)dictionary_get_value(dict, "123", strlen("123"));

    char** all_keys = dictionary_get_all_keys(dict);

    for(int kindex = 0; all_keys[kindex] != 0; kindex++)
    {
        char* key_str = NULL;
        key_str = all_keys[kindex];
        printf("%s\n", key_str);
    }

    dictionary_free_key_list(dict, all_keys);

    dictionary_free(dict);
}

void test_base64(void)
{
    char* old_fname = "/home/subrato/Pictures/testimage.jpg";
    char* new_fname = "/home/subrato/Pictures/testimage_new.jpg";

    FILE* fp = fopen(old_fname, "rb");

    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        long sz = ftell(fp);
        rewind(fp);

        unsigned char* old_image = (char*)calloc(1, sz);
        fread(old_image, sz, 1, fp);
        fclose(fp);

        char* encoded_image = NULL;
        unsigned long encoded_image_len = 0;

        encoded_image = base64_encode(old_image, sz, encoded_image, &encoded_image_len);

        unsigned char* new_image = NULL;
        unsigned long new_image_len = 0;

        new_image = base64_decode(encoded_image, encoded_image_len, new_image, &new_image_len);

        fp = fopen(new_fname, "wb");

        if(fp)
        {
            fwrite(new_image, new_image_len, 1, fp);
            fflush(fp);
            fclose(fp);
        }

        free(encoded_image);
        free(new_image);
    }
}

void test_email(void)
{

}

void test_queue(void)
{

}
