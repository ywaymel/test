void game_new(long long a0, long long a1)
{
    _game_new(8, a0, a1, 1, 0);
    return;
}

long long game_new_empty(void)
{
    return _game_new_empty(8, 1, 0);
}

typedef struct st_500054_2 {
    unsigned int field_0;
    char padding_4[4];
    struct st_500054_1 *field_8;
    struct st_500054_1 *field_10;
} st_500054_2;

typedef struct st_500054_0 {
    unsigned int field_0;
    unsigned int field_4;
    struct st_500054_1 *field_8;
    struct st_500054_1 *field_10;
    char field_18;
} st_500054_0;

typedef struct st_500054_1 {
    unsigned int field_0;
} st_500054_1;

st_500054_2 * game_copy(st_500054_0 *a0)
{
    unsigned int i;  // [bp-0x18]
    unsigned int j;  // [bp-0x14]
    st_500054_2 *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    ptr = _game_new_empty(a0->field_0, a0->field_4, a0->field_18);
    for (i = 0; i < a0->field_0; i += 1)
    {
        for (j = 0; j < a0->field_0; j += 1)
        {
            *(int *)&ptr->field_8[j + i * ptr->field_0 & 0xffffffff] = *(int *)&a0->field_8[j + i * a0->field_0 & 0xffffffff];
            *(int *)&ptr->field_10[j + i * ptr->field_0 & 0xffffffff] = *(int *)&a0->field_10[j + i * a0->field_0 & 0xffffffff];
        }
    }
    return ptr;
}

typedef struct st_50018e_0 {
    unsigned int field_0;
    unsigned int field_4;
    struct st_50018e_1 *field_8;
    struct st_50018e_1 *field_10;
    char field_18;
} st_50018e_0;

typedef struct st_50018e_1 {
    unsigned int field_0;
} st_50018e_1;

unsigned int game_equal(st_50018e_0 *a0, st_50018e_0 *a1)
{
    unsigned int i;  // [bp-0x10]
    unsigned int j;  // [bp-0xc]

    if (a0 && a1)
    {
        if (a0->field_0 != a1->field_0 || a0->field_4 != a1->field_4 || a0->field_18 != a1->field_18)
            return 0;
        for (i = 0; i < a0->field_0; i += 1)
        {
            for (j = 0; j < a0->field_0; j += 1)
            {
                if (*(int *)&a0->field_8[j + i * a0->field_0 & 0xffffffff] != *(int *)&a1->field_8[j + i * a1->field_0 & 0xffffffff] || *(int *)&a0->field_10[j + i * a0->field_0 & 0xffffffff] != *(int *)&a1->field_10[j + i * a1->field_0 & 0xffffffff])
                    return 0;
            }
        }
        return 1;
        return 0;
    }
    __assert_fail(); /* do not return */
}

extern unsigned long got.free;

void game_delete(void* *a0)
{
    if (a0)
    {
        free(a0[1]);
        free(a0[2]);
        queue_free_full(a0[4], got.free);
        queue_free_full(a0[5], got.free);
        free(a0);
        return;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_50039e_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_50039e_1 *field_8;
} st_50039e_0;

typedef struct st_50039e_1 {
    unsigned int field_0;
} st_50039e_1;

void game_set_square(st_50039e_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
    {
        if (a3 && a3 != 1 && a3 != 2)
            __assert_fail(); /* do not return */
        *(unsigned int *)&a0->field_8[a2 + a1 * a0->field_0 & 0xffffffff] = a3;
        return;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_500460_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_500460_1 *field_8;
} st_500460_0;

typedef struct st_500460_1 {
    unsigned int field_0;
} st_500460_1;

int game_get_square(st_500460_0 *a0, unsigned int a1, unsigned int a2)
{
    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
        return *(int *)&a0->field_8[a2 + a1 * a0->field_0 & 0xffffffff];
    __assert_fail(); /* do not return */
}

typedef struct st_5004e1_0 {
    unsigned int field_0;
    char padding_4[12];
    struct st_5004e1_1 *field_10;
} st_5004e1_0;

typedef struct st_5004e1_1 {
    unsigned int field_0;
} st_5004e1_1;

void game_set_region(st_5004e1_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    if (a0 && a1 < a0->field_0 && a2 < a0->field_0 && a3 < a0->field_0)
    {
        *(unsigned int *)&a0->field_10[a2 + a1 * a0->field_0 & 0xffffffff] = a3;
        return;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_500574_0 {
    unsigned int field_0;
    char padding_4[12];
    struct st_500574_1 *field_10;
} st_500574_0;

typedef struct st_500574_1 {
    unsigned int field_0;
} st_500574_1;

int game_get_region(st_500574_0 *a0, unsigned int a1, unsigned int a2)
{
    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
        return *(int *)&a0->field_10[a2 + a1 * a0->field_0 & 0xffffffff];
    __assert_fail(); /* do not return */
}

int game_size(unsigned int *a0)
{
    if (a0)
        return *a0;
    __assert_fail(); /* do not return */
}

typedef struct st_50063c_1 {
    unsigned int field_0;
} st_50063c_1;

typedef struct st_50063c_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_50063c_1 *field_8;
    char padding_10[16];
    long long field_20;
    void* field_28;
} st_50063c_0;

void game_play_move(st_50063c_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    long long v0;  // [bp-0x18]
    long long v1;  // [bp-0x10]

    if ((char)game_check_move(a0, a1, a2, a3))
    {
        v0 = CONCAT(a2, a1);
        v1 = CONCAT(a3, *(int *)&a0->field_8[a2 + a1 * a0->field_0 & 0xffffffff]);
        _stack_clear(a0->field_28);
        _stack_push_move(a0->field_20, v0, v1);
        *(unsigned int *)&a0->field_8[a2 + a1 * a0->field_0 & 0xffffffff] = a3;
        return;
    }
    __assert_fail(); /* do not return */
}

unsigned int game_check_move(unsigned int *a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    unsigned int v1;  // eax

    if (!a0)
        __assert_fail(); /* do not return */
    if (a1 < *a0 && a2 < *a0 && (!a3 || a3 == 1 || a3 == 2))
        v1 = 1;
    else
        v1 = 0;
    return v1 & 1;
}

typedef struct st_5007a5_0 {
    unsigned int field_0;
    unsigned int field_4;
    struct st_5007a5_1 *field_8;
    struct st_5007a5_1 *field_10;
} st_5007a5_0;

typedef struct st_5007a5_1 {
    unsigned int field_0;
} st_5007a5_1;

unsigned int game_is_conflicting(st_5007a5_0 *a0, unsigned int a1, unsigned int a2)
{
    unsigned int v1;  // eax
    unsigned int v2;  // eax
    unsigned int v3;  // eax
    unsigned int v4;  // eax

    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
    {
        if (*(int *)&a0->field_8[a2 + a1 * a0->field_0 & 0xffffffff] != 1)
            return 0;
        v1 = game_nb_squares_row(a0, a1, 1);
        if (a0->field_4 < v1 || (v2 = game_nb_squares_col(a0, a2, 1), a0->field_4 < (unsigned int)game_nb_squares_col(a0, a2, 1) || (v3 = game_nb_squares_region(a0, *(int *)&a0->field_10[a2 + a1 * a0->field_0 & 0xffffffff], 1), a0->field_4 < (unsigned int)game_nb_squares_region(a0, *(int *)&a0->field_10[a2 + a1 * a0->field_0 & 0xffffffff], 1) || game_is_neigh(a0, a1, a2, 1, 1))))
            v4 = 1;
        else
            v4 = 0;
        return v4 & 1;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_5008ed_0 {
    unsigned int field_0;
    unsigned int field_4;
    struct st_5008ed_1 *field_8;
} st_5008ed_0;

typedef struct st_5008ed_1 {
    unsigned int field_0;
} st_5008ed_1;

unsigned int game_won(st_5008ed_0 *a0)
{
    unsigned int v4;  // eax
    unsigned int v5;  // eax
    unsigned int v6;  // eax
    unsigned int i;  // [bp-0x14]
    unsigned int j;  // [bp-0x10]
    unsigned int k;  // [bp-0xc]

    if (!a0)
        __assert_fail(); /* do not return */
    for (i = 0; i < a0->field_0; i += 1)
    {
        v4 = game_nb_squares_row(a0, i, 1);
        if (v4 != a0->field_4)
            return 0;
        v5 = game_nb_squares_col(a0, i, 1);
        if (v5 != a0->field_4)
            return 0;
        v6 = game_nb_squares_region(a0, i, 1);
        if (v6 != a0->field_4)
            return 0;
    }
    for (j = 0; j < a0->field_0; j += 1)
    {
        for (k = 0; k < a0->field_0; k += 1)
        {
            if (*(int *)&a0->field_8[k + j * a0->field_0 & 0xffffffff] == 1 && game_is_neigh(a0, j, k, 1, 1))
                return 0;
        }
    }
    return 1;
}

typedef struct st_500a5a_0 {
    unsigned int field_0;
    unsigned int field_4;
    struct st_500a5a_1 *field_8;
    struct st_500a5a_1 *field_10;
} st_500a5a_0;

typedef struct st_500a5a_1 {
    unsigned int field_0;
} st_500a5a_1;

long long game_fill_cross_queen(st_500a5a_0 *a0)
{
    unsigned long v3;  // rax
    unsigned int v4;  // eax
    unsigned int v5;  // eax
    unsigned int v6;  // eax
    unsigned int v0;  // [bp-0x10]
    unsigned int i;  // [bp-0xc]

    if (!a0)
        __assert_fail(); /* do not return */
    v0 = 0;
    while (1)
    {
        v3 = a0->field_0;
        if (v0 >= (unsigned int)v3)
            break;
        for (i = 0; i < a0->field_0; i += 1)
        {
            if (!*(int *)&a0->field_8[i + v0 * a0->field_0 & 0xffffffff] && (game_is_neigh(a0, v0, i, 1, 1) || (v4 = game_nb_squares_row(a0, v0, 1), (unsigned int)game_nb_squares_row(a0, v0, 1) >= a0->field_4 || (v5 = game_nb_squares_col(a0, i, 1), (unsigned int)game_nb_squares_col(a0, i, 1) >= a0->field_4 || (v6 = game_nb_squares_region(a0, *(int *)&a0->field_10[i + v0 * a0->field_0 & 0xffffffff], 1), (unsigned int)game_nb_squares_region(a0, *(int *)&a0->field_10[i + v0 * a0->field_0 & 0xffffffff], 1) >= a0->field_4)))))
                game_play_move(a0, v0, i, 2);
        }
        v0 += 1;
    }
    return v3;
}

typedef struct st_50063c_1 {
    unsigned int field_0;
} st_50063c_1;

typedef struct st_50063c_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_50063c_1 *field_8;
    char padding_10[16];
    long long field_20;
    void* field_28;
} st_50063c_0;

long long game_remove_cross(st_50063c_0 *a0)
{
    unsigned long v3;  // rax
    unsigned int v0;  // [bp-0x10]
    unsigned int i;  // [bp-0xc]

    if (!a0)
        __assert_fail(); /* do not return */
    v0 = 0;
    while (1)
    {
        v3 = a0->field_0;
        if (v0 >= (unsigned int)v3)
            break;
        for (i = 0; i < a0->field_0; i += 1)
        {
            if (*(int *)&a0->field_8[i + v0 * a0->field_0 & 0xffffffff] == 2)
                game_play_move(a0, v0, i, 0);
        }
        v0 += 1;
    }
    return v3;
}

typedef struct st_500c83_0 {
    unsigned int field_0;
    char padding_4[4];
    unsigned long long field_8;
    char padding_10[16];
    void* field_20;
    void* field_28;
} st_500c83_0;

void game_restart(st_500c83_0 *a0)
{
    unsigned int i;  // [bp-0x10]
    unsigned int j;  // [bp-0xc]

    if (!a0)
        __assert_fail(); /* do not return */
    for (i = 0; i < a0->field_0; i += 1)
    {
        for (j = 0; j < a0->field_0; j += 1)
        {
            *(unsigned int *)((j + i * a0->field_0 & 0xffffffff) * 4 + a0->field_8) = 0;
        }
    }
    _stack_clear(a0->field_20);
    _stack_clear(a0->field_28);
    return;
}

typedef struct st_600000_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_600000_1 *field_8;
    struct st_600000_1 *field_10;
} st_600000_0;

typedef struct st_600000_1 {
    unsigned int field_0;
} st_600000_1;

extern char g_601184;

int game_print(st_600000_0 *a0, char a1)
{
    char v6;  // al
    unsigned int i;  // [bp-0x1c]
    unsigned int j;  // [bp-0x18]
    unsigned int k;  // [bp-0x14]
    unsigned int m;  // [bp-0x10]
    unsigned int l;  // [bp-0xc]

    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (a0->field_0 > 10)
    {
        __assert_fail(); /* do not return */
    }
    else
    {
        puts("Squares:");
        printf("   ");
        for (i = 0; i < a0->field_0; i += 1)
        {
            printf("%u ", i);
        }
        putchar(10);
        printf("  +");
        for (j = 0; j < a0->field_0 * 2; j += 1)
        {
            putchar(45);
        }
        puts("+");
        for (k = 0; k < a0->field_0; k += 1)
        {
            printf("%u |", k);
            for (m = 0; m < a0->field_0; m += 1)
            {
                if (a1)
                    _print_region_color(*(int *)&a0->field_10[m + k * a0->field_0 & 0xffffffff]);
                v6 = _square2str(*(int *)&a0->field_8[m + k * a0->field_0 & 0xffffffff]);
                printf("%u%c", *(int *)&a0->field_10[m + k * a0->field_0 & 0xffffffff], v6);
                if (a1)
                    printf(&g_601184);
            }
            puts("|");
        }
        printf("  +");
        for (l = 0; l < a0->field_0 * 2; l += 1)
        {
            putchar(45);
        }
        return puts("+");
    }
}

long long game_default(void)
{
    unsigned long long v66;  // rcx
    unsigned long long *iter;  // rdi
    unsigned long long v0;  // [bp-0x218]
    unsigned int v1;  // [bp-0x118]
    unsigned int v2;  // [bp-0x114]
    unsigned int v3;  // [bp-0x110]
    unsigned int v4;  // [bp-0x10c]
    unsigned int v5;  // [bp-0x108]
    unsigned int v6;  // [bp-0x104]
    unsigned int v7;  // [bp-0x100]
    unsigned int v8;  // [bp-0xfc]
    unsigned int v9;  // [bp-0xf8]
    unsigned int v10;  // [bp-0xf4]
    unsigned int v11;  // [bp-0xf0]
    unsigned int v12;  // [bp-0xec]
    unsigned int v13;  // [bp-0xe8]
    unsigned int v14;  // [bp-0xe4]
    unsigned int v15;  // [bp-0xe0]
    unsigned int v16;  // [bp-0xdc]
    unsigned int v17;  // [bp-0xd8]
    unsigned int v18;  // [bp-0xd4]
    unsigned int v19;  // [bp-0xd0]
    unsigned int v20;  // [bp-0xcc]
    unsigned int v21;  // [bp-0xc8]
    unsigned int v22;  // [bp-0xc4]
    unsigned int v23;  // [bp-0xc0]
    unsigned int v24;  // [bp-0xbc]
    unsigned int v25;  // [bp-0xb8]
    unsigned int v26;  // [bp-0xb4]
    unsigned int v27;  // [bp-0xb0]
    unsigned int v28;  // [bp-0xac]
    unsigned int v29;  // [bp-0xa8]
    unsigned int v30;  // [bp-0xa4]
    unsigned int v31;  // [bp-0xa0]
    unsigned int v32;  // [bp-0x9c]
    unsigned int v33;  // [bp-0x98]
    unsigned int v34;  // [bp-0x94]
    unsigned int v35;  // [bp-0x90]
    unsigned int v36;  // [bp-0x8c]
    unsigned int v37;  // [bp-0x88]
    unsigned int v38;  // [bp-0x84]
    unsigned int v39;  // [bp-0x80]
    unsigned int v40;  // [bp-0x7c]
    unsigned int v41;  // [bp-0x78]
    unsigned int v42;  // [bp-0x74]
    unsigned int v43;  // [bp-0x70]
    unsigned int v44;  // [bp-0x6c]
    unsigned int v45;  // [bp-0x68]
    unsigned int v46;  // [bp-0x64]
    unsigned int v47;  // [bp-0x60]
    unsigned int v48;  // [bp-0x5c]
    unsigned int v49;  // [bp-0x58]
    unsigned int v50;  // [bp-0x54]
    unsigned int v51;  // [bp-0x50]
    unsigned int v52;  // [bp-0x4c]
    unsigned int v53;  // [bp-0x48]
    unsigned int v54;  // [bp-0x44]
    unsigned int v55;  // [bp-0x40]
    unsigned int v56;  // [bp-0x3c]
    unsigned int v57;  // [bp-0x38]
    unsigned int v58;  // [bp-0x34]
    unsigned int v59;  // [bp-0x30]
    unsigned int v60;  // [bp-0x2c]
    unsigned int v61;  // [bp-0x28]
    unsigned int v62;  // [bp-0x24]
    unsigned int v63;  // [bp-0x20]
    unsigned int v64;  // [bp-0x1c]

    v66 = 32;
    for (iter = &v0; v66; iter += 1)
    {
        v66 -= 1;
        *iter = 0;
    }
    v1 = 0;
    v2 = 0;
    v3 = 3;
    v4 = 1;
    v5 = 1;
    v6 = 1;
    v7 = 1;
    v8 = 1;
    v9 = 0;
    v10 = 0;
    v11 = 3;
    v12 = 1;
    v13 = 1;
    v14 = 1;
    v15 = 1;
    v16 = 1;
    v17 = 0;
    v18 = 2;
    v19 = 3;
    v20 = 1;
    v21 = 1;
    v22 = 1;
    v23 = 1;
    v24 = 1;
    v25 = 3;
    v26 = 3;
    v27 = 3;
    v28 = 3;
    v29 = 1;
    v30 = 4;
    v31 = 4;
    v32 = 4;
    v33 = 6;
    v34 = 6;
    v35 = 6;
    v36 = 6;
    v37 = 4;
    v38 = 4;
    v39 = 4;
    v40 = 4;
    v41 = 6;
    v42 = 6;
    v43 = 6;
    v44 = 6;
    v45 = 4;
    v46 = 4;
    v47 = 5;
    v48 = 5;
    v49 = 6;
    v50 = 6;
    v51 = 6;
    v52 = 6;
    v53 = 6;
    v54 = 6;
    v55 = 7;
    v56 = 5;
    v57 = 6;
    v58 = 6;
    v59 = 6;
    v60 = 6;
    v61 = 6;
    v62 = 6;
    v63 = 7;
    v64 = 5;
    return (unsigned long long)game_new(&v0, &v1);
}

typedef struct st_60050f_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_60050f_1 *field_8;
} st_60050f_0;

typedef struct st_60050f_1 {
    unsigned int field_0;
} st_60050f_1;

st_60050f_0 * game_default_solution(void)
{
    unsigned int i;  // [bp-0x48]
    unsigned int j;  // [bp-0x44]
    st_60050f_0 *v2;  // [bp-0x40]
    unsigned int v3;  // [bp-0x38]
    unsigned int v4;  // [bp-0x34]
    unsigned int v5;  // [bp-0x30]
    unsigned int v6;  // [bp-0x2c]
    unsigned int v7;  // [bp-0x28]
    unsigned int v8;  // [bp-0x24]
    unsigned int v9;  // [bp-0x20]
    unsigned int v10;  // [bp-0x1c]

    v2 = game_default();
    v3 = 0;
    v4 = 4;
    v5 = 1;
    v6 = 3;
    v7 = 5;
    v8 = 7;
    v9 = 2;
    v10 = 6;
    for (i = 0; i < v2->field_0; i += 1)
    {
        for (j = 0; j < v2->field_0; j += 1)
        {
            *(unsigned int *)&v2->field_8[j + i * v2->field_0 & 0xffffffff] = (j == (&v3)[i] ? 1 : 2);
        }
    }
    return v2;
}

typedef struct st_6005f1_0 {
    unsigned int field_0;
    char padding_4[20];
    char field_18;
} st_6005f1_0;

extern unsigned int dir_2_offset[4];

unsigned int game_get_adjacent_square(st_6005f1_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int *a4, unsigned int *a5)
{
    unsigned int v0;  // [bp-0x18]
    unsigned int v1;  // [bp-0x14]
    unsigned int *v2;  // [bp-0x10]
    unsigned int *v3;  // [bp-0xc]

    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
    {
        if (a3 > 8)
            __assert_fail(); /* do not return */
        if (a4 && a5 && a4 != a5)
        {
            v2 = (unsigned int *)dir_2_offset[2 * a3];
            v3 = (unsigned int *)dir_2_offset[1 + 2 * a3];
            if (a0->field_18 ^ 1 && (v2 < NULL && !a1 || v2 > NULL && a1 == a0->field_0 - 1 || v3 < NULL && !a2 || v3 > NULL && a2 == a0->field_0 - 1))
                return 0;
            v0 = a1;
            v1 = a2;
            if (v2 < NULL)
                v0 = (!a1 ? a0->field_0 - 1 : a1 - 1);
            if (v2 > NULL)
                v0 = (a1 == a0->field_0 - 1 ? 0 : a1 + 1);
            if (v3 < NULL)
                v1 = (!a2 ? a0->field_0 - 1 : a2 - 1);
            if (v3 > NULL)
                v1 = (a2 == a0->field_0 - 1 ? 0 : a2 + 1);
            *a4 = v0;
            *a5 = v1;
            return 1;
        }
        __assert_fail(); /* do not return */
    }
    __assert_fail(); /* do not return */
}

typedef struct st_6005f1_0 {
    unsigned int field_0;
    char padding_4[20];
    char field_18;
} st_6005f1_0;

long long game_nb_neigh(st_6005f1_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3, char a4)
{
    unsigned int v0;  // [bp-0x20]
    unsigned int v1;  // [bp-0x1c]
    unsigned int v2;  // [bp-0x18]
    unsigned int i;  // [bp-0x14]

    if (a0 && a1 < a0->field_0 && a2 < a0->field_0)
    {
        if (a3 && a3 != 1 && a3 != 2)
            __assert_fail(); /* do not return */
        v2 = 0;
        for (i = 1; (!a4 ? 4 : 8) >= i; i += 1)
        {
            if ((char)game_get_adjacent_square(a0, a1, a2, i, &v0, &v1) && a3 == *(int *)((v1 + v0 * a0->field_0 & 0xffffffff) * 4 + *(long long *)&a0->padding_4[4]))
                v2 += 1;
        }
        return v2;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_6005f1_0 {
    unsigned int field_0;
    char padding_4[20];
    char field_18;
} st_6005f1_0;

char game_is_neigh(st_6005f1_0 *a0, unsigned int a1, unsigned int a2, unsigned int a3, char a4)
{
    return (int)game_nb_neigh(a0, a1, a2, a3, a4) != 0;
}

typedef struct st_600982_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_600982_1 *field_8;
} st_600982_0;

typedef struct st_600982_1 {
    unsigned int field_0;
} st_600982_1;

unsigned int game_nb_squares_row(st_600982_0 *a0, unsigned int a1, unsigned int a2)
{
    unsigned int v0;  // [bp-0x10]
    unsigned int i;  // [bp-0xc]

    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (a1 >= a0->field_0)
    {
        __assert_fail(); /* do not return */
    }
    else
    {
        if (a2 && a2 != 1 && a2 != 2)
            __assert_fail(); /* do not return */
        v0 = 0;
        for (i = 0; i + 1 < a0->field_0; i += 1)
        {
            if (a2 == *(int *)&a0->field_8[i + a1 * a0->field_0 & 0xffffffff])
                v0 += 1;
        }
        return v0;
    }
}

typedef struct st_600a8a_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_600a8a_1 *field_8;
} st_600a8a_0;

typedef struct st_600a8a_1 {
    unsigned int field_0;
} st_600a8a_1;

unsigned int game_nb_squares_col(st_600a8a_0 *a0, unsigned int a1, unsigned int a2)
{
    unsigned int v0;  // [bp-0x10]
    unsigned int i;  // [bp-0xc]

    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (a1 >= a0->field_0)
    {
        __assert_fail(); /* do not return */
    }
    else
    {
        if (a2 && a2 != 1 && a2 != 2)
            __assert_fail(); /* do not return */
        v0 = 0;
        for (i = 0; i < a0->field_0; i += 1)
        {
            if (a2 == *(int *)&a0->field_8[a1 + i * a0->field_0 & 0xffffffff])
                v0 += 1;
        }
        return v0;
    }
}

typedef struct st_600b8d_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_600b8d_1 *field_8;
    struct st_600b8d_1 *field_10;
} st_600b8d_0;

typedef struct st_600b8d_1 {
    unsigned int field_0;
} st_600b8d_1;

unsigned int game_nb_squares_region(st_600b8d_0 *a0, unsigned int a1, unsigned int a2)
{
    unsigned int v0;  // [bp-0x14]
    unsigned int i;  // [bp-0x10]
    unsigned int j;  // [bp-0xc]

    if (a0 && a1 < a0->field_0)
    {
        if (a2 && a2 != 1 && a2 != 2)
            __assert_fail(); /* do not return */
        v0 = 0;
        for (i = 0; i < a0->field_0; i += 1)
        {
            for (j = 0; j < a0->field_0; j += 1)
            {
                if (a1 == *(int *)&a0->field_10[j + i * a0->field_0 & 0xffffffff] && a2 == *(int *)&a0->field_8[j + i * a0->field_0 & 0xffffffff])
                    v0 += 1;
            }
        }
        return v0;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_600ca9_0 {
    unsigned int field_0;
    char padding_4[4];
    struct st_600ca9_1 *field_8;
} st_600ca9_0;

typedef struct st_600ca9_1 {
    unsigned int field_0;
} st_600ca9_1;

unsigned int game_nb_squares(st_600ca9_0 *a0, unsigned int a1)
{
    unsigned int v0;  // [bp-0x14]
    unsigned int i;  // [bp-0x10]
    unsigned int j;  // [bp-0xc]

    if (!a0)
        __assert_fail(); /* do not return */
    if (a1 && a1 != 1 && a1 != 2)
        __assert_fail(); /* do not return */
    v0 = 0;
    for (i = 0; i < a0->field_0; i += 1)
    {
        for (j = 0; j < a0->field_0; j += 1)
        {
            if (a1 == *(int *)&a0->field_8[j + i * a0->field_0 & 0xffffffff])
                v0 += 1;
        }
    }
    return v0;
}

typedef struct st_6005f1_0 {
    unsigned int field_0;
    char padding_4[20];
    char field_18;
} st_6005f1_0;

long long game_valid_regions(st_6005f1_0 *a0)
{
    unsigned int v19;  // eax
    unsigned int v20;  // eax
    char v0;  // [bp-0x61]
    unsigned int v1;  // [bp-0x60]
    unsigned int v2;  // [bp-0x5c]
    unsigned int v3;  // [bp-0x58]
    unsigned int i;  // [bp-0x54]
    unsigned int j;  // [bp-0x50]
    unsigned int v6;  // [bp-0x4c]
    unsigned int v7;  // [bp-0x4c]
    unsigned int k;  // [bp-0x48]
    unsigned int v9;  // [bp-0x44]
    unsigned int v10;  // [bp-0x40]
    unsigned int v11;  // [bp-0x3c]
    unsigned int v12;  // [bp-0x38]
    unsigned int v13;  // [bp-0x34]
    unsigned long v14;  // [bp-0x30]
    char *ptr;  // [bp-0x28]
    char *ptr1;  // [bp-0x20]
    unsigned int *ptr2;  // [bp-0x18]

    if (!a0)
        __assert_fail(); /* do not return */
    v14 = a0->field_0 * a0->field_0;
    ptr = calloc(v14, 1);
    if (!ptr)
        __assert_fail(); /* do not return */
    ptr1 = calloc(a0->field_0, 1);
    if (!ptr1)
        __assert_fail(); /* do not return */
    ptr2 = calloc(v14, 4);
    if (!ptr2)
        __assert_fail(); /* do not return */
    v3 = 0;
    v0 = 1;
    for (i = 0; i < v14 && v0; i += 1)
    {
        if (!ptr[i])
        {
            v9 = *(int *)(*(long long *)&a0->padding_4[12] + i * 4);
            if (v9 >= a0->field_0 || ptr1[v9])
            {
                v0 = 0;
                break;
            }
            else
            {
                ptr1[v9] = 1;
                v3 += 1;
                j = 0;
                v6 = 0;
                v7 = v6 + 1;
                ptr2[v6] = i;
                ptr[i] = 1;
                while (j < v7)
                {
                    v19 = j;
                    j = v19 + 1;
                    v10 = ptr2[v19];
                    v11 = v10 / a0->field_0;
                    v12 = v10 % a0->field_0;
                    for (k = 1; k <= 4; k += 1)
                    {
                        if (!((char)game_get_adjacent_square(a0, v11, v12, k, &v1, &v2) ^ 1))
                        {
                            v13 = v2 + v1 * a0->field_0;
                            if (ptr[v13] ^ 1 && v9 == *(int *)(*(long long *)&a0->padding_4[12] + v13 * 4))
                            {
                                ptr[v13] = 1;
                                v6 = v7 + 1;
                                ptr2[v7] = v13;
                                v7 = v6;
                            }
                        }
                    }
                }
            }
        }
    }
    free(ptr);
    free(ptr1);
    free(ptr2);
    if (v0 && v3 == a0->field_0)
        v20 = 1;
    else
        v20 = 0;
    return v20 & 1;
}

extern unsigned long stderr;

int watermark(void)
{
    fwrite("Copyright: Queens Game by University of Bordeaux, 2026.\n", 1, 56, stderr);
    return system("date >> watermark");
}

typedef struct st_6005f1_0 {
    unsigned int field_0;
    char padding_4[20];
    char field_18;
} st_6005f1_0;

st_6005f1_0 * _game_new(unsigned int a0, unsigned int *a1, unsigned int *a2, unsigned int a3, char a4)
{
    unsigned int i;  // [bp-0x18]
    unsigned int j;  // [bp-0x14]
    st_6005f1_0 *ptr;  // [bp-0x10]

    if (a1 && a2)
    {
        ptr = _game_new_empty(a0, a3, a4);
        for (i = 0; i < a0; i += 1)
        {
            for (j = 0; j < a0; j += 1)
            {
                game_set_square(ptr, i, j, a1[j + i * ptr->field_0 & 0xffffffff]);
                game_set_region(ptr, i, j, a2[j + i * ptr->field_0 & 0xffffffff]);
            }
        }
        if ((char)game_valid_regions(ptr))
            return ptr;
        __assert_fail(); /* do not return */
    }
    __assert_fail(); /* do not return */
}

typedef struct st_700185_0 {
    unsigned int field_0;
    unsigned int field_4;
    void* field_8;
    void* field_10;
    char field_18;
    char padding_19[7];
    unsigned long long field_20;
    unsigned long long field_28;
} st_700185_0;

st_700185_0 * _game_new_empty(unsigned int a0, unsigned int a1, char a2)
{
    st_700185_0 *ptr;  // [bp-0x10]

    if (!(char)_game_valid_options(a0, a1, a2))
        __assert_fail(); /* do not return */
    ptr = calloc(1, 48);
    if (!ptr)
        __assert_fail(); /* do not return */
    ptr->field_0 = a0;
    ptr->field_4 = a1;
    ptr->field_18 = a2;
    ptr->field_8 = calloc(a0 * a0, 4);
    if (!ptr->field_8)
        __assert_fail(); /* do not return */
    ptr->field_10 = calloc(a0 * a0, 4);
    if (ptr->field_10)
    {
        ptr->field_20 = queue_new();
        ptr->field_28 = queue_new();
        return ptr;
    }
    __assert_fail(); /* do not return */
}

extern char g_70074f;

void _print_region_color(unsigned int a0)
{
    printf(&g_70074f, *(int *)(8 * (a0 & 15) + 7341988), *(int *)(8 * (a0 & 15) + 7341984));
    return;
}

unsigned int _square2str(unsigned int a0)
{
    return (!a0 ? 46 : a0 == 1 ? 42 : a0 == 2 ? 120 : 63);
}

unsigned int _str2square(char a0)
{
    return (a0 == 46 ? 0 : a0 == 42 ? 1 : a0 == 120 ? 2 : 0xffffffff);
}

void _stack_push_move(void* a0, unsigned long a1, unsigned long a2)
{
    unsigned long long *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    ptr = calloc(1, 16);
    if (ptr)
    {
        *ptr = a1;
        ptr[1] = a2;
        queue_push_head(a0, ptr);
        return;
    }
    __assert_fail(); /* do not return */
}

long long _stack_pop_move(void* a0)
{
    unsigned long long *ptr;  // [bp-0x20]
    unsigned long v1;  // [bp-0x18]
    unsigned long v2;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    ptr = queue_pop_head(a0);
    if (ptr)
    {
        v1 = *ptr;
        v2 = ptr[1];
        free(ptr);
        return v1;
    }
    __assert_fail(); /* do not return */
}

long long _stack_is_empty(void* a0)
{
    if (a0)
        return queue_is_empty(a0);
    __assert_fail(); /* do not return */
}

extern unsigned long got.free;

void _stack_clear(void* a0)
{
    if (!a0)
        __assert_fail(); /* do not return */
    queue_clear_full(a0, got.free);
    if ((char)queue_is_empty(a0))
        return;
    __assert_fail(); /* do not return */
}

unsigned int _game_valid_options(unsigned int a0, unsigned int a1, char a2)
{
    unsigned int v1;  // eax

    if (a0 && a1 && a0 >= a1 && (a2 ^ 1 || a0 > 2))
        v1 = 1;
    else
        v1 = 0;
    return v1 & 1;
}

typedef struct st_800000_0 {
    unsigned long long field_0;
    unsigned long long field_8;
    unsigned int field_10;
} st_800000_0;

st_800000_0 * queue_new(void)
{
    st_800000_0 *ptr;  // [bp-0x10]

    ptr = malloc(24);
    if (ptr)
    {
        ptr->field_10 = 0;
        ptr->field_0 = 0;
        ptr->field_8 = ptr->field_0;
        return ptr;
    }
    __assert_fail(); /* do not return */
}

typedef struct st_800074_1 {
    struct st_800074_0 *field_0;
    struct st_800074_0 *field_8;
    unsigned int field_10;
} st_800074_1;

typedef struct st_800074_0 {
    unsigned long long field_0;
    struct st_800074_0 *field_8;
    struct st_800074_0 *field_10;
} st_800074_0;

void queue_push_head(st_800074_1 *a0, unsigned long a1)
{
    st_800074_0 *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    ptr = malloc(24);
    if (!ptr)
        __assert_fail(); /* do not return */
    ptr->field_0 = a1;
    ptr->field_10 = NULL;
    ptr->field_8 = a0->field_0;
    if (a0->field_0)
        a0->field_0->field_10 = ptr;
    a0->field_0 = ptr;
    if (!a0->field_8)
        a0->field_8 = ptr;
    a0->field_10 = a0->field_10 + 1;
    return;
}

typedef struct st_80016d_1 {
    struct st_80016d_0 *field_0;
    struct st_80016d_0 *field_8;
    unsigned int field_10;
} st_80016d_1;

typedef struct st_80016d_0 {
    unsigned long long field_0;
    struct st_80016d_0 *field_8;
    struct st_80016d_0 *field_10;
} st_80016d_0;

st_80016d_1 * queue_push_tail(st_80016d_1 *a0, unsigned long a1)
{
    st_80016d_0 *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    ptr = malloc(24);
    if (!ptr)
        __assert_fail(); /* do not return */
    ptr->field_0 = a1;
    ptr->field_10 = a0->field_8;
    ptr->field_8 = NULL;
    if (a0->field_8)
        a0->field_8->field_8 = ptr;
    a0->field_8 = ptr;
    if (!a0->field_0)
        a0->field_0 = ptr;
    a0->field_10 = a0->field_10 + 1;
    return a0;
}

typedef struct st_800268_1 {
    unsigned long long field_0;
    struct st_800268_0 *field_8;
} st_800268_1;

typedef struct st_800268_2 {
    struct st_800268_1 *field_0;
    unsigned long long field_8;
    unsigned int field_10;
} st_800268_2;

typedef struct st_800268_0 {
    char padding_0[16];
    unsigned long long field_10;
} st_800268_0;

unsigned long long queue_pop_head(st_800268_2 *a0)
{
    unsigned long v0;  // [bp-0x18]
    st_800268_0 *v1;  // [bp-0x10]

    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (!a0->field_10)
    {
        __assert_fail(); /* do not return */
    }
    else if (!a0->field_0)
    {
        return 0;
    }
    else
    {
        v0 = a0->field_0->field_0;
        v1 = a0->field_0->field_8;
        if (v1)
            v1->field_10 = 0;
        free(a0->field_0);
        a0->field_0 = v1;
        a0->field_10 = a0->field_10 - 1;
        if (a0->field_0)
            return v0;
        a0->field_8 = 0;
        return v0;
    }
}

typedef struct st_800366_0 {
    char padding_0[8];
    unsigned long long field_8;
} st_800366_0;

typedef struct st_800366_2 {
    unsigned long long field_0;
    struct st_800366_1 *field_8;
    unsigned int field_10;
} st_800366_2;

typedef struct st_800366_1 {
    unsigned long long field_0;
    char padding_8[8];
    struct st_800366_0 *field_10;
} st_800366_1;

unsigned long long queue_pop_tail(st_800366_2 *a0)
{
    unsigned long v0;  // [bp-0x18]
    st_800366_0 *v1;  // [bp-0x10]

    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (!a0->field_10)
    {
        __assert_fail(); /* do not return */
    }
    else if (!a0->field_8)
    {
        return 0;
    }
    else
    {
        v0 = a0->field_8->field_0;
        v1 = a0->field_8->field_10;
        if (v1)
            v1->field_8 = 0;
        free(a0->field_8);
        a0->field_8 = v1;
        a0->field_10 = a0->field_10 - 1;
        if (a0->field_8)
            return v0;
        a0->field_0 = 0;
        return v0;
    }
}

typedef struct st_800469_0 {
    char padding_0[16];
    unsigned int field_10;
} st_800469_0;

int queue_length(st_800469_0 *a0)
{
    if (a0)
        return a0->field_10;
    __assert_fail(); /* do not return */
}

typedef struct st_8004b1_0 {
    char padding_0[16];
    unsigned int field_10;
} st_8004b1_0;

long long queue_is_empty(st_8004b1_0 *a0)
{
    unsigned long v1;  // rax

    if (a0)
    {
        v1 = a0->field_10;
        return _INSERT(v1, 0, !(unsigned int)v1);
    }
    __assert_fail(); /* do not return */
}

typedef struct st_8004fe_0 {
    unsigned long long field_0;
} st_8004fe_0;

long long queue_peek_head(st_8004fe_0 **a0)
{
    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (!*a0)
    {
        __assert_fail(); /* do not return */
    }
    else
    {
        return *(long long *)*a0;
    }
}

typedef struct st_80057d_0 {
    char padding_0[8];
    struct st_80057d_1 *field_8;
} st_80057d_0;

typedef struct st_80057d_1 {
    unsigned long long field_0;
} st_80057d_1;

long long queue_peek_tail(st_80057d_0 *a0)
{
    if (!a0)
    {
        __assert_fail(); /* do not return */
    }
    else if (!a0->field_8)
    {
        __assert_fail(); /* do not return */
    }
    else
    {
        return *(long long *)a0->field_8;
    }
}

typedef struct st_8005fe_0 {
    char padding_0[8];
    struct st_8005fe_0 *field_8;
} st_8005fe_0;

typedef struct st_8005fe_1 {
    struct st_8005fe_0 *field_0;
    struct st_8005fe_0 *field_8;
    unsigned int field_10;
} st_8005fe_1;

void queue_clear(st_8005fe_1 *a0)
{
    st_8005fe_0 *iter;  // [bp-0x18]
    st_8005fe_0 *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    iter = a0->field_0;
    while (iter)
    {
        ptr = iter;
        iter = iter->field_8;
        free(ptr);
    }
    a0->field_8 = NULL;
    a0->field_0 = a0->field_8;
    a0->field_10 = 0;
    return;
}

typedef struct st_80069a_0 {
    unsigned long long field_0;
    struct st_80069a_0 *field_8;
} st_80069a_0;

typedef struct st_80069a_1 {
    struct st_80069a_0 *field_0;
    struct st_80069a_0 *field_8;
    unsigned int field_10;
} st_80069a_1;

void queue_clear_full(st_80069a_1 *a0, unsigned long long *a1)
{
    st_80069a_0 *iter;  // [bp-0x18]
    st_80069a_0 *ptr;  // [bp-0x10]

    if (!a0)
        __assert_fail(); /* do not return */
    iter = a0->field_0;
    while (iter)
    {
        ptr = iter;
        if (a1)
            a1(iter->field_0);
        iter = iter->field_8;
        free(ptr);
    }
    a0->field_8 = NULL;
    a0->field_0 = a0->field_8;
    a0->field_10 = 0;
    return;
}

void queue_free(void* a0)
{
    queue_clear(a0);
    free(a0);
    return;
}

void queue_free_full(void* a0, unsigned long long *a1)
{
    queue_clear_full(a0, a1);
    free(a0);
    return;
}
