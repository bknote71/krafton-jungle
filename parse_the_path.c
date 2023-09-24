#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define true 1
#define false 0

typedef int bool;

struct dir
{
    struct dir_entry *entry[20];
    int entrys;
};

struct dir_entry
{
    char name[20];

    // 이게 만약 sub dir 이면 ??
    bool is_dir;
    struct dir inode;
};

struct path
{
    struct dir *arr[20];
    char file_name[20];
    int dcount;
};

struct dir *root;
struct dir *cur_dir;

int contains(struct dir *dir, const char *file_name)
{
    for (int i = 0; i < dir->entrys; ++i)
    {
        if (strcmp(dir->entry[i]->name, file_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

struct path *
parse_file_path(const char *file_path)
{
    int file_length;
    if ((file_length = strlen(file_path)) == 0)
        return NULL;

    // absolute path
    int is_absol = file_path[0] == '.';
    struct dir *dir = is_absol ? root : cur_dir;
    int ns = is_absol ? 1 : (file_path[1] != '.' ? 2 : 3);

    // path 구조체 생성
    struct path *path = malloc(sizeof(struct path));
    path->arr[path->dcount++] = dir;

    while (1)
    {
        // 다음 '/' 가 있는지 체크
        // find_next_slash
        char tmp_name[20] = { 0 };
        int i;

        for (i = ns; i < file_length; ++i)
            if (file_path[i] == '/')
                break;

        if (i == file_length) // 찾지 못함, so ns 부터 끝까지 파일명
        {
            // path->file_name 에 해당하는 파일이 dir 에 없으면 null
            strcpy(tmp_name, (file_path + ns));

            if (contains(dir, tmp_name) == -1)
            {
                free(path);
                return NULL;
            }

            strcpy(path->file_name, file_path + ns);
            break;
        }
        else
        {
            // ns ~ (i - 1) 글자 카피: i - ns 개
            int entry_idx;
            strncpy(tmp_name, file_path + ns, i - ns);

            if ((entry_idx = contains(dir, tmp_name)) == -1)
            {
                free(path);
                return NULL;
            }

            // entry idx
            struct dir_entry *p = dir->entry[entry_idx];
            path->arr[path->dcount++] = &p->inode;
            dir = &p->inode;
        }
    }
    return path;
}

int main()
{
    const char absol_path = "/foo/bar.txt";
    const char rel_path = "./foo/koo.txt";
    const char par_path = "../foo/qoo.txt";

    // root 초기화
    root = malloc(sizeof(struct dir));

    struct dir_entry *e1 = malloc(sizeof(struct dir_entry));
    struct dir_entry *e2 = malloc(sizeof(struct dir_entry));
    struct dir_entry *e3 = malloc(sizeof(struct dir_entry));
    struct dir_entry *e4 = malloc(sizeof(struct dir_entry));

    strcpy(e1->name, "foo\0");
    e1->is_dir = true;
    e1->inode.entry[0] = e2;
    e1->inode.entry[1] = e3;
    e1->inode.entry[2] = e4;
    e1->inode.entrys = 3;

    strcpy(e2->name, "bar.txt\0");
    e2->is_dir = false;

    strcpy(e2->name, "koo.txt\0");
    e3->is_dir = false;

    strcpy(e2->name, "qoo.txt\0");
    e4->is_dir = false;

    root->entry[0] = e1;
    root->entrys = 1;

    struct path *p1 = parse_file_path(absol_path);
    // struct path *p2 = parse_file_path(rel_path);
    // struct path *p3 = parse_file_path(par_path);

    printf("p1 ? %d\n", p1 == NULL);
    printf("p1 first dir name: %s\n", p1->arr[0]);
    printf("p1 second dir name: %s\n", p1->arr[1]);
    printf("p1 filename: %s\n", p1->file_name);

    return 0;
}