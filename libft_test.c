/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:33:26 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/20 13:10:55 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#define MAX_FAILS 200 // Maximum number of failed tests to list

// Global variables to track test results
int g_tests_passed = 0;
int g_tests_failed = 0;
int g_total_tests = 0;
static const char *g_failed_test_names[MAX_FAILS];
static int g_failed_test_count = 0;
static int g_failed_list_full_warning_shown = 0;

// Helper function to print test results
void print_test_result(const char *test_name, int success)
{
    printf("  %s: %s\n", test_name, success ? "PASSED" : "FAILED");
    if (success)
        g_tests_passed++;
    else
    {
        g_tests_failed++;
        if (g_failed_test_count < MAX_FAILS)
        {
            g_failed_test_names[g_failed_test_count++] = test_name;
        }
        else if (!g_failed_list_full_warning_shown)
        {
            printf("  [Warning: Maximum number of failed tests (%d) reached. List truncated.]\n", MAX_FAILS);
            g_failed_list_full_warning_shown = 1;
        }
    }
    g_total_tests++;
}

// Helper to compare memory regions (using memcmp)
int compare_memory(const void *s1, const void *s2, size_t n)
{
    return memcmp(s1, s2, n) == 0;
}

// Helper function to free the array returned by ft_split
void free_split_array(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Helper for ft_strmapi test
char mapi_test_func(unsigned int i, char c)
{
    (void)i;                // Avoid unused warning if index not needed
    return (ft_toupper(c)); // Example: convert char to uppercase
}

// Helper for ft_striteri test
void iteri_test_func(unsigned int i, char *c)
{
    (void)i;             // Avoid unused warning if index not needed
    *c = ft_tolower(*c); // Example: convert char to lowercase
}

// --- Helper functions for list tests ---

// Function to create a new int*, useful for list content
int *create_int_ptr(int value)
{
    int *ptr = malloc(sizeof(int));
    if (ptr)
        *ptr = value;
    return ptr;
}

// Function to print the list (for debugging, not used in pass/fail)
void print_int_list(t_list *lst)
{
    printf("List: [");
    while (lst)
    {
        if (lst->content)
            printf("%d", *(int *)(lst->content));
        else
            printf("(null content)");
        lst = lst->next;
        if (lst)
            printf(", ");
    }
    printf("]\\n");
}

// Simple deletion function for list content (int*)
void del_int_content(void *content)
{
    free(content);
}

// Iteration function: increment the int value
void iter_increment_int(void *content)
{
    if (content)
    {
        (*(int *)content)++;
    }
}

// Mapping function: create new int* with value + 1
void *map_increment_int(void *content)
{
    if (!content)
        return NULL;
    int *original_value = (int *)content;
    int *new_value = malloc(sizeof(int));
    if (!new_value)
        return NULL;
    *new_value = *original_value + 1;
    return new_value;
}

int main(void)
{
    char buffer1[100];
    char buffer2[100];
    // char *str_result; // No longer needed as ft_substr, ft_strjoin etc. are removed
    char **split_result;
    int i;

    printf("--- Testing libft Functions (Based on Provided Prototypes) ---\n");

    // ft_isalpha
    printf("\nTesting ft_isalpha...\n");
    print_test_result("'a'", ft_isalpha('a') != 0);
    print_test_result("'Z'", ft_isalpha('Z') != 0);
    print_test_result("'1'", ft_isalpha('1') == 0);
    print_test_result("Space", ft_isalpha(' ') == 0);
    print_test_result("Null char", ft_isalpha('\0') == 0);
    print_test_result("EOF (-1)", ft_isalpha(EOF) == 0);
    print_test_result("128", ft_isalpha(128) == 0);

    // ft_isdigit
    printf("\nTesting ft_isdigit...\n");
    print_test_result("'0'", ft_isdigit('0') != 0);
    print_test_result("'9'", ft_isdigit('9') != 0);
    print_test_result("'a'", ft_isdigit('a') == 0);
    print_test_result("Space", ft_isdigit(' ') == 0);
    print_test_result("Null char", ft_isdigit('\0') == 0);

    // ft_isalnum
    printf("\nTesting ft_isalnum...\n");
    print_test_result("'a'", ft_isalnum('a') != 0);
    print_test_result("'Z'", ft_isalnum('Z') != 0);
    print_test_result("'0'", ft_isalnum('0') != 0);
    print_test_result("'9'", ft_isalnum('9') != 0);
    print_test_result("'@'", ft_isalnum('@') == 0);
    print_test_result("Space", ft_isalnum(' ') == 0);

    // ft_isascii
    printf("\nTesting ft_isascii...\n");
    print_test_result("'a'", ft_isascii('a') != 0);
    print_test_result("Null char (0)", ft_isascii(0) != 0);
    print_test_result("127", ft_isascii(127) != 0);
    print_test_result("128", ft_isascii(128) == 0);
    print_test_result("-1", ft_isascii(-1) == 0);

    // ft_isprint
    printf("\nTesting ft_isprint...\n");
    print_test_result("Space (32)", ft_isprint(' ') != 0);
    print_test_result("'~' (126)", ft_isprint('~') != 0);
    print_test_result("Tab (9)", ft_isprint('\t') == 0);
    print_test_result("Del (127)", ft_isprint(127) == 0);
    print_test_result("Null char (0)", ft_isprint('\0') == 0);

    // ft_strlen
    printf("\nTesting ft_strlen...\n");
    print_test_result("Empty string", ft_strlen("") == strlen(""));
    print_test_result("Short string", ft_strlen("Hello") == strlen("Hello"));
    print_test_result("Long string", ft_strlen("This is a longer test string.") == strlen("This is a longer test string."));

    // ft_memset
    printf("\nTesting ft_memset...\n");
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer1, 'A', 10);
    ft_memset(buffer2, 'A', 10);
    print_test_result("Basic fill", compare_memory(buffer1, buffer2, 15));
    memset(buffer1 + 2, 'B', 5);
    ft_memset(buffer2 + 2, 'B', 5);
    print_test_result("Partial fill", compare_memory(buffer1, buffer2, 15));
    memcpy(buffer1, "Original", 9);
    memcpy(buffer2, "Original", 9);
    void *ret_ft_memset = ft_memset(buffer2 + 3, 'C', 0);
    print_test_result("Zero size (content)", compare_memory(buffer1, buffer2, 9));
    print_test_result("Zero size (return ptr)", ret_ft_memset == (buffer2 + 3));
    memset(buffer1, 0, 10);
    ft_memset(buffer2, 0, 10);
    print_test_result("Fill with nulls", compare_memory(buffer1, buffer2, 15));

    // ft_bzero
    printf("\nTesting ft_bzero...\n");
    memset(buffer1, 'X', 15);
    memset(buffer2, 'X', 15);
    bzero(buffer1 + 3, 5);
    ft_bzero(buffer2 + 3, 5);
    print_test_result("Partial zero", compare_memory(buffer1, buffer2, 15));
    memcpy(buffer1, "Original", 9);
    memcpy(buffer2, "Original", 9);
    bzero(buffer1 + 2, 0);
    ft_bzero(buffer2 + 2, 0);
    print_test_result("Zero size", compare_memory(buffer1, buffer2, 9));
    bzero(buffer1, 10);
    ft_bzero(buffer2, 10);
    print_test_result("Full zero (start)", compare_memory(buffer1, buffer2, 15));

    // ft_memcpy
    printf("\nTesting ft_memcpy...\n");
    char src_memcpy[] = "Source String";
    memset(buffer1, 'A', 20);
    memset(buffer2, 'A', 20);
    memcpy(buffer1, src_memcpy, strlen(src_memcpy) + 1);
    void *ret_ft_memcpy = ft_memcpy(buffer2, src_memcpy, strlen(src_memcpy) + 1);
    print_test_result("Basic copy (content)", compare_memory(buffer1, buffer2, strlen(src_memcpy) + 5));
    print_test_result("Basic copy (return ptr)", ret_ft_memcpy == buffer2);
    memcpy(buffer1, "Original", 9);
    memcpy(buffer2, "Original", 9);
    ret_ft_memcpy = ft_memcpy(buffer2, src_memcpy, 0);
    print_test_result("Zero size (content)", compare_memory(buffer1, buffer2, 9));
    print_test_result("Zero size (return ptr)", ret_ft_memcpy == buffer2);
    memcpy(buffer1, "Test\0Hidden", 11);
    ft_memcpy(buffer2, "Test\0Hidden", 11);
    print_test_result("Copy with embedded null", compare_memory(buffer1, buffer2, 11));

    // ft_memmove
    printf("\nTesting ft_memmove...\n");
    char memmove_str[] = "1234567890";
    char dest1[20];
    char dest2[20];
    void *ret_ft_memmove;
    strcpy(dest1, memmove_str);
    strcpy(dest2, memmove_str);
    memmove(dest1 + 2, dest1, 5);
    ret_ft_memmove = ft_memmove(dest2 + 2, dest2, 5);
    print_test_result("Overlap dest > src (content)", strcmp(dest1, dest2) == 0);
    print_test_result("Overlap dest > src (return ptr)", ret_ft_memmove == (dest2 + 2));
    strcpy(dest1, memmove_str);
    strcpy(dest2, memmove_str);
    memmove(dest1, dest1 + 2, 5);
    ret_ft_memmove = ft_memmove(dest2, dest2 + 2, 5);
    print_test_result("Overlap src > dest (content)", strcmp(dest1, dest2) == 0);
    print_test_result("Overlap src > dest (return ptr)", ret_ft_memmove == dest2);
    strcpy(dest1, memmove_str);
    strcpy(dest2, memmove_str);
    memmove(dest1 + 5, dest1, 3);
    ret_ft_memmove = ft_memmove(dest2 + 5, dest2, 3);
    print_test_result("No overlap (content)", strcmp(dest1, dest2) == 0);
    print_test_result("No overlap (return ptr)", ret_ft_memmove == (dest2 + 5));
    strcpy(dest1, memmove_str);
    strcpy(dest2, memmove_str);
    memmove(dest1 + 2, dest1, 0);
    ret_ft_memmove = ft_memmove(dest2 + 2, dest2, 0);
    print_test_result("Zero size (content)", strcmp(dest1, memmove_str) == 0 && strcmp(dest2, memmove_str) == 0);
    print_test_result("Zero size (return ptr)", ret_ft_memmove == (dest2 + 2));

    // ft_strlcpy (Requires <bsd/string.h> on Linux, often included in libc on BSD/macOS)
    printf("\nTesting ft_strlcpy...\n");
    char dst_lcpy[20];
    size_t res_lcpy_std, res_lcpy_ft;
    memset(dst_lcpy, 'A', sizeof(dst_lcpy));
    res_lcpy_std = strlcpy(buffer1, "Hello", 20);
    res_lcpy_ft = ft_strlcpy(dst_lcpy, "Hello", 20);
    print_test_result("Basic copy content", strcmp(dst_lcpy, "Hello") == 0 && strcmp(buffer1, dst_lcpy) == 0);
    print_test_result("Basic copy return", res_lcpy_ft == 5 && res_lcpy_ft == res_lcpy_std);
    memset(dst_lcpy, 'A', sizeof(dst_lcpy));
    res_lcpy_std = strlcpy(buffer1, "World Wide Web", 6);
    res_lcpy_ft = ft_strlcpy(dst_lcpy, "World Wide Web", 6);
    print_test_result("Truncation content", strcmp(dst_lcpy, "World") == 0 && strcmp(buffer1, dst_lcpy) == 0);
    print_test_result("Truncation return", res_lcpy_ft == 14 && res_lcpy_ft == res_lcpy_std);
    memset(dst_lcpy, 'A', sizeof(dst_lcpy));
    res_lcpy_std = strlcpy(buffer1, "Test", 1);
    res_lcpy_ft = ft_strlcpy(dst_lcpy, "Test", 1);
    print_test_result("Size 1 content", dst_lcpy[0] == '\0' && strcmp(buffer1, dst_lcpy) == 0);
    print_test_result("Size 1 return", res_lcpy_ft == 4 && res_lcpy_ft == res_lcpy_std);
    memset(dst_lcpy, 'A', sizeof(dst_lcpy));
    dst_lcpy[1] = '\0';
    buffer1[0] = 'X';
    res_lcpy_std = strlcpy(buffer1, "Test", 0);
    res_lcpy_ft = ft_strlcpy(dst_lcpy, "Test", 0);
    print_test_result("Size 0 content unchanged", dst_lcpy[0] == 'A');
    print_test_result("Size 0 return", res_lcpy_ft == 4 && res_lcpy_ft == res_lcpy_std);
    memset(dst_lcpy, 'A', sizeof(dst_lcpy));
    res_lcpy_std = strlcpy(buffer1, "", 20);
    res_lcpy_ft = ft_strlcpy(dst_lcpy, "", 20);
    print_test_result("Empty src content", strcmp(dst_lcpy, "") == 0 && strcmp(buffer1, dst_lcpy) == 0);
    print_test_result("Empty src return", res_lcpy_ft == 0 && res_lcpy_ft == res_lcpy_std);

    // ft_strlcat (Requires <bsd/string.h> on Linux, often included in libc on BSD/macOS)
    printf("\nTesting ft_strlcat...\n");
    char dst_lcat[20];
    size_t res_lcat_std, res_lcat_ft;
    strcpy(dst_lcat, "Hello ");
    strcpy(buffer1, "Hello ");
    res_lcat_std = strlcat(buffer1, "World!", 20);
    res_lcat_ft = ft_strlcat(dst_lcat, "World!", 20);
    print_test_result("Basic concat content", strcmp(dst_lcat, "Hello World!") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Basic concat return", res_lcat_ft == 12 && res_lcat_ft == res_lcat_std);
    strcpy(dst_lcat, "Test ");
    strcpy(buffer1, "Test ");
    res_lcat_std = strlcat(buffer1, "Concatenation", 10);
    res_lcat_ft = ft_strlcat(dst_lcat, "Concatenation", 10);
    print_test_result("Truncation content", strcmp(dst_lcat, "Test Conc") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Truncation return", res_lcat_ft == 18 && res_lcat_ft == res_lcat_std);
    strcpy(dst_lcat, "123456789");
    strcpy(buffer1, "123456789");
    res_lcat_std = strlcat(buffer1, "More", 10);
    res_lcat_ft = ft_strlcat(dst_lcat, "More", 10);
    print_test_result("Dst almost full content", strcmp(dst_lcat, "123456789") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Dst almost full return", res_lcat_ft == 13 && res_lcat_ft == res_lcat_std);
    strcpy(dst_lcat, "Buffer Full");
    strcpy(buffer1, "Buffer Full");
    res_lcat_std = strlcat(buffer1, "Data", 5);
    res_lcat_ft = ft_strlcat(dst_lcat, "Data", 5);
    print_test_result("Size <= dstlen content", strcmp(dst_lcat, "Buffer Full") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Size <= dstlen return", res_lcat_ft == 9 && res_lcat_ft == res_lcat_std);
    strcpy(dst_lcat, "Check");
    strcpy(buffer1, "Check");
    res_lcat_std = strlcat(buffer1, "", 10);
    res_lcat_ft = ft_strlcat(dst_lcat, "", 10);
    print_test_result("Empty src content", strcmp(dst_lcat, "Check") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Empty src return", res_lcat_ft == 5 && res_lcat_ft == res_lcat_std);
    dst_lcat[0] = '\0';
    buffer1[0] = '\0';
    res_lcat_std = strlcat(buffer1, "Start", 10);
    res_lcat_ft = ft_strlcat(dst_lcat, "Start", 10);
    print_test_result("Empty dst content", strcmp(dst_lcat, "Start") == 0 && strcmp(buffer1, dst_lcat) == 0);
    print_test_result("Empty dst return", res_lcat_ft == 5 && res_lcat_ft == res_lcat_std);

    // ft_toupper
    printf("\nTesting ft_toupper...\n");
    print_test_result("'a' to 'A'", ft_toupper('a') == toupper('a'));
    print_test_result("'z' to 'Z'", ft_toupper('z') == toupper('z'));
    print_test_result("'A' stays 'A'", ft_toupper('A') == toupper('A'));
    print_test_result("'5' stays '5'", ft_toupper('5') == toupper('5'));
    print_test_result("Space stays space", ft_toupper(' ') == toupper(' '));
    print_test_result("EOF", ft_toupper(EOF) == toupper(EOF));

    // ft_tolower
    printf("\nTesting ft_tolower...\n");
    print_test_result("'A' to 'a'", ft_tolower('A') == tolower('A'));
    print_test_result("'Z' to 'z'", ft_tolower('Z') == tolower('Z'));
    print_test_result("'a' stays 'a'", ft_tolower('a') == tolower('a'));
    print_test_result("'9' stays '9'", ft_tolower('9') == tolower('9'));
    print_test_result("Space stays space", ft_tolower(' ') == tolower(' '));
    print_test_result("EOF", ft_tolower(EOF) == tolower(EOF));

    // ft_strchr
    printf("\nTesting ft_strchr...\n");
    char strchr_str[] = "Find the char.";
    print_test_result("Find 't'", ft_strchr(strchr_str, 't') == strchr(strchr_str, 't'));
    print_test_result("Find '.'", ft_strchr(strchr_str, '.') == strchr(strchr_str, '.'));
    print_test_result("Find '\0'", ft_strchr(strchr_str, '\0') == strchr(strchr_str, '\0'));
    print_test_result("Not found 'z'", ft_strchr(strchr_str, 'z') == strchr(strchr_str, 'z'));
    print_test_result("Empty string find 'a'", ft_strchr("", 'a') == strchr("", 'a'));
    print_test_result("Empty string find '\0'", ft_strchr("", '\0') == strchr("", '\0'));
    // print_test_result("NULL string find 'a'", ft_strchr(NULL, 'a') == strchr(NULL, 'a')); // Assuming returns NULL

    // ft_strrchr
    printf("\nTesting ft_strrchr...\n");
    char strrchr_str[] = "Find the last char char.";
    print_test_result("Find last 'h'", ft_strrchr(strrchr_str, 'h') == strrchr(strrchr_str, 'h'));
    print_test_result("Find last 'c'", ft_strrchr(strrchr_str, 'c') == strrchr(strrchr_str, 'c')); // Should be index 18
    print_test_result("Find last '.'", ft_strrchr(strrchr_str, '.') == strrchr(strrchr_str, '.'));
    print_test_result("Find '\0'", ft_strrchr(strrchr_str, '\0') == strrchr(strrchr_str, '\0'));
    print_test_result("Not found 'z'", ft_strrchr(strrchr_str, 'z') == strrchr(strrchr_str, 'z'));
    print_test_result("Find first char 'F'", ft_strrchr(strrchr_str, 'F') == strrchr(strrchr_str, 'F'));
    print_test_result("Empty string find 'a'", ft_strrchr("", 'a') == strrchr("", 'a'));
    print_test_result("Empty string find '\0'", ft_strrchr("", '\0') == strrchr("", '\0'));
    // print_test_result("NULL string find 'a'", ft_strrchr(NULL, 'a') == NULL); // Assuming returns NULL

    // ft_strncmp
    printf("\nTesting ft_strncmp...\n");
#define CMP_SIGN(x) ((x) == 0 ? 0 : ((x) > 0 ? 1 : -1))
    print_test_result("Equal strings, n > len", ft_strncmp("abc", "abc", 5) == 0);
    print_test_result("Equal strings, n = len", ft_strncmp("abc", "abc", 3) == 0);
    print_test_result("Equal prefix, n < len", ft_strncmp("abcdef", "abcghi", 3) == 0);
    print_test_result("s1 > s2 ('d' > 'c')", CMP_SIGN(ft_strncmp("abd", "abc", 3)) == CMP_SIGN(strncmp("abd", "abc", 3)));
    print_test_result("s1 < s2 ('c' < 'd')", CMP_SIGN(ft_strncmp("abc", "abd", 3)) == CMP_SIGN(strncmp("abc", "abd", 3)));
    print_test_result("Empty strings", ft_strncmp("", "", 5) == 0);
    print_test_result("One empty string (s1 > s2)", CMP_SIGN(ft_strncmp("a", "", 1)) == CMP_SIGN(strncmp("a", "", 1)));
    print_test_result("One empty string (s1 < s2)", CMP_SIGN(ft_strncmp("", "a", 1)) == CMP_SIGN(strncmp("", "a", 1)));
    print_test_result("n = 0", ft_strncmp("abc", "abd", 0) == 0);
    print_test_result("Different lengths, match n", ft_strncmp("abcdef", "abcghi", 3) == 0);
    print_test_result("Compare non-ASCII (\\xFF > \\xFE)", CMP_SIGN(ft_strncmp("ab\xFF", "ab\xFE", 3)) == CMP_SIGN(strncmp("ab\xFF", "ab\xFE", 3)));
    // print_test_result("NULL s1", CMP_SIGN(ft_strncmp(NULL, "abc", 3)) < 0); // Behavior might vary, assuming NULL is "less"
    // print_test_result("NULL s2", CMP_SIGN(ft_strncmp("abc", NULL, 3)) > 0); // Behavior might vary, assuming non-NULL is "greater"
    // print_test_result("NULL s1 and s2", ft_strncmp(NULL, NULL, 3) == 0);    // Assuming equal

    // ft_memchr
    printf("\nTesting ft_memchr...\n");
    char memchr_str[] = "ab\0cde";
    print_test_result("Find 'c'", ft_memchr(memchr_str, 'c', 6) == memchr(memchr_str, 'c', 6));
    print_test_result("Find '\0'", ft_memchr(memchr_str, '\0', 6) == memchr(memchr_str, '\0', 6));
    print_test_result("Not found 'z'", ft_memchr(memchr_str, 'z', 6) == memchr(memchr_str, 'z', 6));
    print_test_result("Find at start", ft_memchr(memchr_str, 'a', 6) == memchr(memchr_str, 'a', 6));
    print_test_result("Find at end (within n)", ft_memchr(memchr_str, 'e', 6) == memchr(memchr_str, 'e', 6));
    print_test_result("Search size 0", ft_memchr(memchr_str, 'a', 0) == memchr(memchr_str, 'a', 0));
    print_test_result("Find beyond n", ft_memchr(memchr_str, 'd', 4) == memchr(memchr_str, 'd', 4));
    print_test_result("Find exactly at n-1", ft_memchr(memchr_str, 'd', 5) == memchr(memchr_str, 'd', 5));
    // print_test_result("NULL input", ft_memchr(NULL, 'a', 5) == NULL); // Assuming returns NULL

    // ft_memcmp
    printf("\nTesting ft_memcmp...\n");
    char memcmp_s1[] = "abCde";
    char memcmp_s2[] = "abcde";
    print_test_result("Equal up to n", CMP_SIGN(ft_memcmp("Test1", "Test2", 4)) == CMP_SIGN(memcmp("Test1", "Test2", 4)));
    print_test_result("Different at byte 3", CMP_SIGN(ft_memcmp(memcmp_s1, memcmp_s2, 5)) == CMP_SIGN(memcmp(memcmp_s1, memcmp_s2, 5)));
    print_test_result("s1 < s2 ('C' < 'c')", CMP_SIGN(ft_memcmp(memcmp_s1, memcmp_s2, 5)) == CMP_SIGN(memcmp(memcmp_s1, memcmp_s2, 5)));
    print_test_result("s1 > s2 (reversed)", CMP_SIGN(ft_memcmp(memcmp_s2, memcmp_s1, 5)) == CMP_SIGN(memcmp(memcmp_s2, memcmp_s1, 5)));
    print_test_result("Compare identical", CMP_SIGN(ft_memcmp("Same", "Same", 5)) == CMP_SIGN(memcmp("Same", "Same", 5)));
    print_test_result("Compare different lengths, identical prefix", CMP_SIGN(ft_memcmp("SameThing", "Same", 4)) == CMP_SIGN(memcmp("SameThing", "Same", 4)));
    print_test_result("Compare different lengths, different after prefix", CMP_SIGN(ft_memcmp("SameThing", "SameElse", 8)) == CMP_SIGN(memcmp("SameThing", "SameElse", 8)));
    print_test_result("Compare with nulls (s1 < s2)", CMP_SIGN(ft_memcmp("ab\0d", "ab\0e", 4)) == CMP_SIGN(memcmp("ab\0d", "ab\0e", 4)));
    print_test_result("Compare with nulls (s1 > s2)", CMP_SIGN(ft_memcmp("ab\0e", "ab\0d", 4)) == CMP_SIGN(memcmp("ab\0e", "ab\0d", 4)));
    print_test_result("n = 0", CMP_SIGN(ft_memcmp("abc", "abd", 0)) == CMP_SIGN(memcmp("abc", "abd", 0)));
    // print_test_result("NULL s1", CMP_SIGN(ft_memcmp(NULL, "abc", 3)) < 0);        // Behavior might vary
    // print_test_result("NULL s2", CMP_SIGN(ft_memcmp("abc", NULL, 3)) > 0);        // Behavior might vary
    // print_test_result("NULL s1 and s2", CMP_SIGN(ft_memcmp(NULL, NULL, 3)) == 0); // Assuming equal

    // ft_strnstr (Often BSD extension, standard C has strstr)
    printf("\nTesting ft_strnstr...\n");
    char haystack[] = "Foo Bar Baz";
    char *ft_res, *std_res;
    ft_res = ft_strnstr(haystack, "Bar", 11);
    std_res = strstr(haystack, "Bar"); // Compare with standard strstr
    print_test_result("Find 'Bar' full length", ft_res == std_res);
    ft_res = ft_strnstr(haystack, "Bar", 7);
    std_res = haystack + 4;
    print_test_result("Find 'Bar' limited length (found)", ft_res == std_res);
    ft_res = ft_strnstr(haystack, "Baz", 8);
    print_test_result("Find 'Baz' limited length (not found)", ft_res == NULL);
    ft_res = ft_strnstr(haystack, "Foo", 11);
    print_test_result("Find 'Foo' at start", ft_res == haystack);
    ft_res = ft_strnstr(haystack, "", 11);
    print_test_result("Find empty needle", ft_res == haystack);
    ft_res = ft_strnstr("", "Bar", 3);
    print_test_result("Find needle in empty haystack", ft_res == NULL);
    char *empty_haystack = "";
    ft_res = ft_strnstr(empty_haystack, "", 0);
    print_test_result("Find empty needle in empty haystack (n=0)", ft_res == empty_haystack);
    ft_res = ft_strnstr(empty_haystack, "", 1);
    print_test_result("Find empty needle in empty haystack (n=1)", ft_res == empty_haystack);
    ft_res = ft_strnstr("abc", "abcde", 5);
    print_test_result("Needle longer than haystack", ft_res == NULL);
    ft_res = ft_strnstr(haystack, "Bar", 0);
    print_test_result("Find with n=0", ft_res == NULL);
    ft_res = ft_strnstr("abcde", "cde", 2);
    print_test_result("Find where needle starts at limit n (not found)", ft_res == NULL);
    char *haystack_local1 = "abcde";
    ft_res = ft_strnstr(haystack_local1, "cde", 3); // n=3 is enough to *start* matching 'c' but not enough for 'd'
    print_test_result("Find where needle starts at limit n (found - check should be NULL)", ft_res == NULL);
    ft_res = ft_strnstr("abc", "bc", 2);
    print_test_result("Needle matches end of n (not found)", ft_res == NULL);
    char *haystack_local2 = "abc";
    ft_res = ft_strnstr(haystack_local2, "bc", 3);
    print_test_result("Needle matches end of n (found)", ft_res == haystack_local2 + 1);
    // print_test_result("NULL haystack", ft_strnstr(NULL, "bar", 3) == NULL);
    // print_test_result("NULL needle", ft_strnstr("foo bar", NULL, 7) == NULL); // Behavior might vary
    // print_test_result("NULL haystack and needle", ft_strnstr(NULL, NULL, 5) == NULL);

    // ft_atoi
    printf("\nTesting ft_atoi...\n");
    // NOTE: Your prototype `int ft_atoi(char *str)` uses non-const char*.
    // Standard atoi is `int atoi(const char *str)`.
    // Passing string literals (like "123") to a function expecting `char *`
    // is technically unsafe, but common if the function doesn't modify the input.
    // Assuming ft_atoi does NOT modify str. Consider changing prototype to use const.
    print_test_result("Basic positive", ft_atoi("123") == atoi("123"));
    print_test_result("Basic negative", ft_atoi("-456") == atoi("-456"));
    print_test_result("Positive with sign", ft_atoi("+789") == atoi("+789"));
    print_test_result("Zero", ft_atoi("0") == atoi("0"));
    print_test_result("Leading whitespace", ft_atoi("  \t\n 42") == atoi("  \t\n 42"));
    print_test_result("Trailing chars", ft_atoi("42abc") == atoi("42abc"));
    print_test_result("Whitespace and sign", ft_atoi("\v\f\r -10") == atoi("\v\f\r -10"));
    print_test_result("Invalid start", ft_atoi("a123") == atoi("a123"));
    print_test_result("Empty string", ft_atoi("") == atoi(""));
    print_test_result("Only whitespace", ft_atoi(" \t\n") == atoi(" \t\n"));
    print_test_result("Only sign +", ft_atoi("+") == atoi("+"));
    print_test_result("Only sign -", ft_atoi("-") == atoi("-"));
    print_test_result("Double sign --", ft_atoi("--1") == atoi("--1"));
    print_test_result("Double sign ++", ft_atoi("++1") == atoi("++1"));
    print_test_result("Sign after number", ft_atoi("1-") == atoi("1-"));
    print_test_result("INT_MAX", ft_atoi("2147483647") == INT_MAX);
    print_test_result("INT_MIN", ft_atoi("-2147483648") == INT_MIN);
    print_test_result("Long positive", ft_atoi("9999999999") == atoi("9999999999"));
    print_test_result("Long negative", ft_atoi("-9999999999") == atoi("-9999999999"));

    // ft_calloc
    printf("\nTesting ft_calloc...\n");
    size_t num = 5;
    size_t size = sizeof(int);
    int *arr_ft, *arr_std;
    arr_ft = (int *)ft_calloc(num, size);
    arr_std = (int *)calloc(num, size);
    if (arr_ft && arr_std)
    {
        print_test_result("Basic allocation (non-NULL)", arr_ft != NULL);
        print_test_result("Memory zeroed", compare_memory(arr_ft, arr_std, num * size));
        free(arr_ft);
        free(arr_std);
    }
    else
    {
        print_test_result("Basic allocation (non-NULL)", 0); // Failed
        print_test_result("Memory zeroed", 0);               // Failed
        free(arr_ft);                                        // Free even if std failed
        free(arr_std);
    }
    arr_ft = ft_calloc(0, size);
    print_test_result("Zero count allocation", arr_ft != NULL); // Should return valid ptr or NULL
    free(arr_ft);
    arr_ft = ft_calloc(num, 0);
    print_test_result("Zero size allocation", arr_ft != NULL); // Should return valid ptr or NULL
    free(arr_ft);
    arr_ft = ft_calloc(0, 0);
    print_test_result("Zero count and size allocation", arr_ft != NULL); // Should return valid ptr or NULL
    free(arr_ft);
    // Test potential overflow - behavior might vary, check if it returns NULL
    arr_ft = ft_calloc(INT_MAX, INT_MAX);
    print_test_result("Overflow allocation (expected NULL)", arr_ft == NULL);
    free(arr_ft);

    // ft_itoa
    printf("\nTesting ft_itoa...\n");
    char *str_itoa;
    str_itoa = ft_itoa(0);
    print_test_result("itoa 0", str_itoa && strcmp(str_itoa, "0") == 0);
    free(str_itoa);
    str_itoa = ft_itoa(123);
    print_test_result("itoa 123", str_itoa && strcmp(str_itoa, "123") == 0);
    free(str_itoa);
    str_itoa = ft_itoa(-456);
    print_test_result("itoa -456", str_itoa && strcmp(str_itoa, "-456") == 0);
    free(str_itoa);
    str_itoa = ft_itoa(INT_MAX);
    print_test_result("itoa INT_MAX", str_itoa && strcmp(str_itoa, "2147483647") == 0);
    free(str_itoa);
    str_itoa = ft_itoa(INT_MIN);
    print_test_result("itoa INT_MIN", str_itoa && strcmp(str_itoa, "-2147483648") == 0);
    free(str_itoa);
    str_itoa = ft_itoa(-0);
    print_test_result("itoa -0", str_itoa && strcmp(str_itoa, "0") == 0);
    free(str_itoa);

    // ft_strdup
    printf("\nTesting ft_strdup...\n");
    char *s_dup1 = "Test string";
    char *dup_ft1, *dup_std1;
    dup_ft1 = ft_strdup(s_dup1);
    dup_std1 = strdup(s_dup1);
    print_test_result("Basic strdup content", dup_ft1 && dup_std1 && strcmp(dup_ft1, dup_std1) == 0);
    print_test_result("Basic strdup pointer different", dup_ft1 != s_dup1);
    free(dup_ft1);
    free(dup_std1);
    char *s_dup2 = "";
    dup_ft1 = ft_strdup(s_dup2);
    dup_std1 = strdup(s_dup2);
    print_test_result("Empty string strdup content", dup_ft1 && dup_std1 && strcmp(dup_ft1, dup_std1) == 0);
    print_test_result("Empty string strdup pointer different", dup_ft1 != s_dup2);
    free(dup_ft1);
    free(dup_std1);
    // dup_ft1 = ft_strdup(NULL);
    // print_test_result("NULL input strdup", dup_ft1 == NULL); // Assuming returns NULL
    // free(dup_ft1);

    // ft_substr
    printf("\nTesting ft_substr...\n");
    char *s_sub = "0123456789";
    char *sub_res;
    sub_res = ft_substr(s_sub, 2, 5);
    print_test_result("Substr middle", sub_res && strcmp(sub_res, "23456") == 0);
    free(sub_res);
    sub_res = ft_substr(s_sub, 0, 3);
    print_test_result("Substr start", sub_res && strcmp(sub_res, "012") == 0);
    free(sub_res);
    sub_res = ft_substr(s_sub, 7, 10);
    print_test_result("Substr end (len > remaining)", sub_res && strcmp(sub_res, "789") == 0);
    free(sub_res);
    sub_res = ft_substr(s_sub, 10, 5);
    print_test_result("Substr start >= len", sub_res && strcmp(sub_res, "") == 0);
    free(sub_res);
    sub_res = ft_substr(s_sub, 5, 0);
    print_test_result("Substr len 0", sub_res && strcmp(sub_res, "") == 0);
    free(sub_res);
    sub_res = ft_substr("", 0, 5);
    print_test_result("Substr empty string", sub_res && strcmp(sub_res, "") == 0);
    free(sub_res);
    // Test NULL input if your function should handle it (standard substr doesn't define behavior)
    sub_res = ft_substr(NULL, 0, 5);
    print_test_result("Substr NULL input", sub_res == NULL); // Or expected behavior
    free(sub_res);
    sub_res = ft_substr(s_sub, 2, SIZE_MAX);                                               // Test potential overflow or large length
    print_test_result("Substr SIZE_MAX len", sub_res && strcmp(sub_res, "23456789") == 0); // Expects rest of string
    free(sub_res);

    // ft_strjoin
    printf("\nTesting ft_strjoin...\n");
    char *s1_join = "Hello, ";
    char *s2_join = "World!";
    char *join_res;
    join_res = ft_strjoin(s1_join, s2_join);
    print_test_result("Basic join", join_res && strcmp(join_res, "Hello, World!") == 0);
    free(join_res);
    join_res = ft_strjoin("", s2_join);
    print_test_result("Join empty s1", join_res && strcmp(join_res, "World!") == 0);
    free(join_res);
    join_res = ft_strjoin(s1_join, "");
    print_test_result("Join empty s2", join_res && strcmp(join_res, "Hello, ") == 0);
    free(join_res);
    join_res = ft_strjoin("", "");
    print_test_result("Join empty s1 and s2", join_res && strcmp(join_res, "") == 0);
    free(join_res);
    // Test NULL inputs if your function should handle them
    join_res = ft_strjoin(NULL, s2_join);
    print_test_result("Join NULL s1", join_res == NULL); // Or expected behavior
    free(join_res);
    join_res = ft_strjoin(s1_join, NULL);
    print_test_result("Join NULL s2", join_res == NULL); // Or expected behavior
    free(join_res);
    join_res = ft_strjoin(NULL, NULL);
    print_test_result("Join NULL s1 and s2", join_res == NULL); // Or expected behavior
    free(join_res);

    // ft_strtrim
    printf("\nTesting ft_strtrim...\n");
    char *s_trim = "  \t Trim me! \n  ";
    char *set_trim = " \t\n";
    char *trim_res;
    trim_res = ft_strtrim(s_trim, set_trim);
    print_test_result("Basic trim", trim_res && strcmp(trim_res, "Trim me!") == 0);
    free(trim_res);
    trim_res = ft_strtrim("NoTrim", set_trim);
    print_test_result("Trim no matching chars", trim_res && strcmp(trim_res, "NoTrim") == 0);
    free(trim_res);
    trim_res = ft_strtrim(s_trim, "");
    print_test_result("Trim empty set", trim_res && strcmp(trim_res, "  \t Trim me! \n  ") == 0);
    free(trim_res);
    trim_res = ft_strtrim("", set_trim);
    print_test_result("Trim empty string", trim_res && strcmp(trim_res, "") == 0);
    free(trim_res);
    trim_res = ft_strtrim(" \t\n ", set_trim);
    print_test_result("Trim string with only set chars", trim_res && strcmp(trim_res, "") == 0);
    free(trim_res);
    trim_res = ft_strtrim("StartTrim", "Start");
    print_test_result("Trim from start only", trim_res && strcmp(trim_res, "Trim") == 0);
    free(trim_res);
    trim_res = ft_strtrim("EndTrimEnd", "End");
    print_test_result("Trim from end only", trim_res && strcmp(trim_res, "Trim") == 0);
    free(trim_res);
    // Test NULL inputs if your function should handle them
    trim_res = ft_strtrim(NULL, set_trim);
    print_test_result("Trim NULL s1", trim_res == NULL);
    free(trim_res);
    trim_res = ft_strtrim(s_trim, NULL);
    print_test_result("Trim NULL set", trim_res == NULL); // Or same as empty set?
    free(trim_res);
    trim_res = ft_strtrim(NULL, NULL);
    print_test_result("Trim NULL s1 and NULL set", trim_res == NULL);
    free(trim_res);

    // ft_split
    printf("\nTesting ft_split...\n");
    char *split_str;
    char c;
    char **expected_split;
    int split_ok;

    split_str = "split  this for   me!";
    c = ' ';
    char *expected1[] = {"split", "this", "for", "me!", NULL};
    expected_split = expected1;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Basic split", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Basic split (allocation fail?)", 0);
    }

    split_str = "abc,def,ghi,jkl";
    c = ',';
    char *expected2[] = {"abc", "def", "ghi", "jkl", NULL};
    expected_split = expected2;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Comma delimiter", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Comma delimiter (allocation fail?)", 0);
    }

    split_str = "NoDelimitersHere";
    c = ' ';
    char *expected3[] = {"NoDelimitersHere", NULL};
    expected_split = expected3;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        split_ok = (split_result[0] != NULL && strcmp(expected_split[0], split_result[0]) == 0 && split_result[1] == NULL);
        print_test_result("No delimiter found", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("No delimiter found (allocation fail?)", 0);
    }

    split_str = "";
    c = ' ';
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        print_test_result("Empty string input (result[0] is NULL)", split_result[0] == NULL);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Empty string input (allocation fail?)", 0);
    }

    split_str = "     ";
    c = ' ';
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        print_test_result("Only delimiters (result[0] is NULL)", split_result[0] == NULL);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Only delimiters (allocation fail?)", 0);
    }

    split_str = " start end ";
    c = ' ';
    char *expected6[] = {"start", "end", NULL};
    expected_split = expected6;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Delimiter at start/end", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Delimiter at start/end (allocation fail?)", 0);
    }

    split_str = "word1,,,word2";
    c = ',';
    char *expected7[] = {"word1", "word2", NULL};
    expected_split = expected7;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Consecutive delimiters middle", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Consecutive delimiters middle (allocation fail?)", 0);
    }

    // Test case for consecutive delimiters at the end
    split_str = "word1,word2,,,";
    c = ',';
    char *expected8[] = {"word1", "word2", NULL};
    expected_split = expected8;
    split_result = ft_split(split_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Consecutive delimiters at end", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Consecutive delimiters at end (allocation fail?)", 0);
    }

    // More extreme test case with many delimiters at the end
    char extreme_delimiter_str[200];
    memset(extreme_delimiter_str, 0, sizeof(extreme_delimiter_str));
    strcpy(extreme_delimiter_str, "start,middle");
    // Add 100 consecutive delimiters at the end
    for (i = 0; i < 100; i++)
    {
        strcat(extreme_delimiter_str, ",");
    }

    c = ',';
    char *expected9[] = {"start", "middle", NULL};
    expected_split = expected9;
    split_result = ft_split(extreme_delimiter_str, c);
    if (split_result)
    {
        i = 0;
        split_ok = 1;
        while (expected_split[i] && split_result[i])
        {
            if (strcmp(expected_split[i], split_result[i]) != 0)
            {
                split_ok = 0;
                break;
            }
            i++;
        }
        if (expected_split[i] != NULL || split_result[i] != NULL)
            split_ok = 0;
        print_test_result("Many consecutive delimiters at end", split_ok);
        free_split_array(split_result);
    }
    else
    {
        print_test_result("Many consecutive delimiters at end (allocation fail?)", 0);
    }

    // Test with tightly sized string with delimiters at end
    // This exact-sized allocation is more likely to trigger memory issues
    char *tight_str = malloc(10);
    if (tight_str)
    {
        strcpy(tight_str, "a,b,,,,"); // Exactly 7 chars + null terminator
        c = ',';
        char *expected10[] = {"a", "b", NULL};
        expected_split = expected10;
        split_result = ft_split(tight_str, c);
        if (split_result)
        {
            i = 0;
            split_ok = 1;
            while (expected_split[i] && split_result[i])
            {
                if (strcmp(expected_split[i], split_result[i]) != 0)
                {
                    split_ok = 0;
                    break;
                }
                i++;
            }
            if (expected_split[i] != NULL || split_result[i] != NULL)
                split_ok = 0;
            print_test_result("Exact-sized allocation with delimiters at end", split_ok);
            free_split_array(split_result);
        }
        else
        {
            print_test_result("Exact-sized allocation (allocation fail?)", 0);
        }
        free(tight_str);
    }

    // Direct test for the fix we're looking for
    printf("\nDirect test for the boundary check issue in ft_split:\n");
    printf("If your code has the 'if(s[i] == '\\'\\0') break;' line, this should pass.\n");
    printf("If that fix is missing, you'll likely see 'free(): invalid pointer' error and crash.\n");

    // Create a string ending with delimiters, but place it at the very end of an allocation
    // This makes it very likely to cause memory access violations without the fix
    char *edge_str = malloc(8); // Just enough for "x,,,\0"
    if (edge_str)
    {
        strcpy(edge_str, "x,,,"); // One word followed by delimiters at the edge of allocation

        printf("Running critical test (may crash if fix is missing)...\n");
        split_result = ft_split(edge_str, ',');

        if (split_result)
        {
            printf("Test passed without crashing!\n");
            free_split_array(split_result);
        }
        free(edge_str);
    }

    // Final attempt - this test creates a custom string that will definitely cause issues
    // if the fix is not present, by placing a poisoned area right after the terminating null
    printf("\nFINAL DETERMINISTIC TEST:\n");
    char *poison_str = malloc(16);
    if (poison_str)
    {
        // Create string with delimiters at end
        strcpy(poison_str, "word,,,,");

        // "Poison" the area right after the string to make it more likely to crash
        // when the boundary check is missing
        for (i = 7; i < 15; i++)
        {
            poison_str[i] = (char)0xFF; // Place invalid data past the end
        }
        poison_str[15] = '\0'; // Ensure proper termination of the poison area

        printf("Testing with poisoned memory area... (will likely crash if fix is missing)\n");
        split_result = ft_split(poison_str, ',');

        if (split_result)
        {
            printf("Your ft_split survived the poison test! The fix is likely present.\n");
            free_split_array(split_result);
        }
        free(poison_str);
    }

    split_result = ft_split(NULL, ',');
    print_test_result("Split NULL input", split_result == NULL); // Assuming returns NULL
    free_split_array(split_result);

    // ft_strmapi
    printf("\nTesting ft_strmapi...\n");
    char *s_mapi = "hello world";
    char *mapi_res = ft_strmapi(s_mapi, mapi_test_func);
    print_test_result("Basic mapi (uppercase)", mapi_res && strcmp(mapi_res, "HELLO WORLD") == 0);
    free(mapi_res);
    mapi_res = ft_strmapi("", mapi_test_func);
    print_test_result("Empty string mapi", mapi_res && strcmp(mapi_res, "") == 0);
    free(mapi_res);
    mapi_res = ft_strmapi(NULL, mapi_test_func);
    print_test_result("NULL string mapi", mapi_res == NULL);
    free(mapi_res);
    mapi_res = ft_strmapi(s_mapi, NULL);
    print_test_result("NULL function mapi", mapi_res == NULL);
    free(mapi_res);

    // ft_striteri
    printf("\nTesting ft_striteri...\n");
    char s_iteri[] = "HELLO WORLD";
    ft_striteri(s_iteri, iteri_test_func);
    print_test_result("Basic iteri (lowercase)", strcmp(s_iteri, "hello world") == 0);
    char s_iteri_empty[] = "";
    ft_striteri(s_iteri_empty, iteri_test_func);
    print_test_result("Empty string iteri", strcmp(s_iteri_empty, "") == 0);
    // Test NULL inputs (should not crash)
    ft_striteri(NULL, iteri_test_func);
    print_test_result("NULL string iteri (no crash)", 1); // Test assumes it just doesn't crash
    strcpy(s_iteri, "TEST");                              // Restore string
    ft_striteri(s_iteri, NULL);
    print_test_result("NULL function iteri (no crash/change)", strcmp(s_iteri, "TEST") == 0);

    // --- File Descriptor Functions ---
    // Note: These tests capture output written to STDOUT (fd=1)
    int pipefd[2];
    int saved_stdout;
    char read_buffer[100];
    ssize_t bytes_read;

// Helper macro for redirecting stdout
#define CAPTURE_STDOUT()                                        \
    do                                                          \
    {                                                           \
        fflush(stdout); /* Ensure previous output is flushed */ \
        saved_stdout = dup(STDOUT_FILENO);                      \
        if (pipe(pipefd) == -1)                                 \
        {                                                       \
            perror("pipe");                                     \
            exit(EXIT_FAILURE);                                 \
        }                                                       \
        dup2(pipefd[1], STDOUT_FILENO);                         \
        close(pipefd[1]);                                       \
    } while (0)

// Helper macro for restoring stdout and reading pipe
#define READ_AND_RESTORE_STDOUT(expected_output, test_name)                      \
    do                                                                           \
    {                                                                            \
        fflush(stdout); /* Ensure function output is written to pipe */          \
        dup2(saved_stdout, STDOUT_FILENO);                                       \
        close(saved_stdout);                                                     \
        bytes_read = read(pipefd[0], read_buffer, sizeof(read_buffer) - 1);      \
        if (bytes_read >= 0)                                                     \
            read_buffer[bytes_read] = '\0';                                      \
        else                                                                     \
            read_buffer[0] = '\0';                                               \
        close(pipefd[0]);                                                        \
        print_test_result(test_name, strcmp(read_buffer, expected_output) == 0); \
    } while (0)

    // ft_putchar_fd
    printf("\nTesting ft_putchar_fd (writing to fd 1)...\n");
    CAPTURE_STDOUT();
    ft_putchar_fd('A', STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("A", "putchar 'A'");
    CAPTURE_STDOUT();
    ft_putchar_fd('\0', STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("\0", "putchar null");
    ft_putchar_fd('X', -1);                          // Test invalid fd (should not crash)
    print_test_result("putchar invalid fd (-1)", 1); // Test assumes no crash

    // ft_putstr_fd
    printf("\nTesting ft_putstr_fd (writing to fd 1)...\n");
    CAPTURE_STDOUT();
    ft_putstr_fd("Hello FD", STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("Hello FD", "putstr basic");
    CAPTURE_STDOUT();
    ft_putstr_fd("", STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("", "putstr empty");
    // Test NULL input
    CAPTURE_STDOUT();
    ft_putstr_fd(NULL, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("", "putstr NULL (empty output)"); // Assuming empty output for NULL
    ft_putstr_fd("Test", -1);                                  // Test invalid fd
    print_test_result("putstr invalid fd (-1)", 1);            // Test assumes no crash

    // ft_putendl_fd
    printf("\nTesting ft_putendl_fd (writing to fd 1)...\n");
    CAPTURE_STDOUT();
    ft_putendl_fd("Line with newline", STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("Line with newline\n", "putendl basic");
    CAPTURE_STDOUT();
    ft_putendl_fd("", STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("\n", "putendl empty");
    // Test NULL input
    CAPTURE_STDOUT();
    ft_putendl_fd(NULL, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("\n", "putendl NULL (newline only)"); // Assuming newline only for NULL
    ft_putendl_fd("Test", -1);                                    // Test invalid fd
    print_test_result("putendl invalid fd (-1)", 1);              // Test assumes no crash

    // ft_putnbr_fd
    printf("\nTesting ft_putnbr_fd (writing to fd 1)...\n");
    CAPTURE_STDOUT();
    ft_putnbr_fd(123, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("123", "putnbr positive");
    CAPTURE_STDOUT();
    ft_putnbr_fd(-456, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("-456", "putnbr negative");
    CAPTURE_STDOUT();
    ft_putnbr_fd(0, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("0", "putnbr zero");
    CAPTURE_STDOUT();
    ft_putnbr_fd(INT_MAX, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("2147483647", "putnbr INT_MAX");
    CAPTURE_STDOUT();
    ft_putnbr_fd(INT_MIN, STDOUT_FILENO);
    READ_AND_RESTORE_STDOUT("-2147483648", "putnbr INT_MIN");
    ft_putnbr_fd(123, -1);                          // Test invalid fd
    print_test_result("putnbr invalid fd (-1)", 1); // Test assumes no crash

    // --- Linked List Functions ---
    printf("\n--- Testing Linked List Functions ---\n");

    t_list *list = NULL;
    t_list *node1, *node2, *node3, *last_node, *mapped_list;
    int *content1, *content2, *content3;
    int list_size;

    // ft_lstnew
    printf("\nTesting ft_lstnew...\n");
    content1 = create_int_ptr(10);
    node1 = ft_lstnew(content1);
    print_test_result("lstnew node created", node1 != NULL);
    print_test_result("lstnew content correct", node1 && node1->content == content1 && *(int *)node1->content == 10);
    print_test_result("lstnew next is NULL", node1 && node1->next == NULL);
    // Note: We don't free content1 here as it's now owned by node1
    ft_lstdelone(node1, del_int_content); // Clean up the created node

    node1 = ft_lstnew(NULL);
    print_test_result("lstnew with NULL content (node exists)", node1 != NULL);
    print_test_result("lstnew with NULL content (content is NULL)", node1 && node1->content == NULL);
    ft_lstdelone(node1, del_int_content); // Clean up

    // ft_lstadd_front
    printf("\nTesting ft_lstadd_front...\n");
    list = NULL;
    content1 = create_int_ptr(1);
    node1 = ft_lstnew(content1);
    ft_lstadd_front(&list, node1);
    print_test_result("lstadd_front to empty list (list points to node1)", list == node1);
    print_test_result("lstadd_front to empty list (node1 content)", list && list->content == content1 && *(int *)list->content == 1);
    print_test_result("lstadd_front to empty list (node1 next is NULL)", list && list->next == NULL);

    content2 = create_int_ptr(0);
    node2 = ft_lstnew(content2);
    ft_lstadd_front(&list, node2);
    print_test_result("lstadd_front to non-empty (list points to node2)", list == node2);
    print_test_result("lstadd_front to non-empty (node2 content)", list && list->content == content2 && *(int *)list->content == 0);
    print_test_result("lstadd_front to non-empty (node2 next is node1)", list && list->next == node1);
    print_test_result("lstadd_front to non-empty (node1 is still last)", list && list->next && list->next == node1 && list->next->next == NULL);

    ft_lstadd_front(NULL, node1); // Should not crash
    print_test_result("lstadd_front with NULL list pointer (no crash)", 1);
    ft_lstadd_front(&list, NULL); // Should not crash / change list
    print_test_result("lstadd_front with NULL new node (no change)", list == node2);

    // Cleanup list for next tests (manual cleanup as ft_lstclear not tested yet)
    free(list->content);       // Free content2 (int*)
    free(list->next->content); // Free content1 (int*)
    free(list->next);          // Free node1
    free(list);                // Free node2
    list = NULL;

    // ft_lstsize
    printf("\nTesting ft_lstsize...\n");
    list = NULL;
    print_test_result("lstsize empty list", ft_lstsize(list) == 0);
    content1 = create_int_ptr(1);
    node1 = ft_lstnew(content1);
    ft_lstadd_front(&list, node1);
    print_test_result("lstsize one element", ft_lstsize(list) == 1);
    content2 = create_int_ptr(2);
    node2 = ft_lstnew(content2);
    ft_lstadd_front(&list, node2);
    print_test_result("lstsize two elements", ft_lstsize(list) == 2);
    content3 = create_int_ptr(3);
    node3 = ft_lstnew(content3);
    ft_lstadd_front(&list, node3);
    print_test_result("lstsize three elements", ft_lstsize(list) == 3);
    ft_lstclear(&list, del_int_content); // Use ft_lstclear now for cleanup

    // ft_lstlast
    printf("\nTesting ft_lstlast...\n");
    list = NULL;
    print_test_result("lstlast empty list", ft_lstlast(list) == NULL);
    content1 = create_int_ptr(10);
    node1 = ft_lstnew(content1);
    list = node1;
    print_test_result("lstlast one element", ft_lstlast(list) == node1);
    content2 = create_int_ptr(20);
    node2 = ft_lstnew(content2);
    list->next = node2; // Manually add for this test
    print_test_result("lstlast two elements", ft_lstlast(list) == node2);
    content3 = create_int_ptr(30);
    node3 = ft_lstnew(content3);
    node2->next = node3;
    print_test_result("lstlast three elements", ft_lstlast(list) == node3);
    ft_lstclear(&list, del_int_content);

    // ft_lstadd_back
    printf("\nTesting ft_lstadd_back...\n");
    list = NULL;
    content1 = create_int_ptr(100);
    node1 = ft_lstnew(content1);
    ft_lstadd_back(&list, node1); // Add to empty list
    print_test_result("lstadd_back to empty (list points to node1)", list == node1);
    print_test_result("lstadd_back to empty (node1 content)", list && list->content == content1 && *(int *)list->content == 100);
    print_test_result("lstadd_back to empty (node1 next is NULL)", list && list->next == NULL);

    content2 = create_int_ptr(200);
    node2 = ft_lstnew(content2);
    ft_lstadd_back(&list, node2); // Add to list with one element
    last_node = ft_lstlast(list);
    print_test_result("lstadd_back to non-empty (last is node2)", last_node == node2);
    print_test_result("lstadd_back to non-empty (node2 content)", last_node && last_node->content == content2 && *(int *)last_node->content == 200);
    print_test_result("lstadd_back to non-empty (node2 next is NULL)", last_node && last_node->next == NULL);
    print_test_result("lstadd_back to non-empty (list size is 2)", ft_lstsize(list) == 2);

    content3 = create_int_ptr(300);
    node3 = ft_lstnew(content3);
    ft_lstadd_back(&list, node3); // Add to list with two elements
    last_node = ft_lstlast(list);
    print_test_result("lstadd_back successive (last is node3)", last_node == node3);
    print_test_result("lstadd_back successive (node3 content)", last_node && last_node->content == content3 && *(int *)last_node->content == 300);
    print_test_result("lstadd_back successive (list size is 3)", ft_lstsize(list) == 3);

    ft_lstadd_back(NULL, node1); // Should not crash
    print_test_result("lstadd_back with NULL list pointer (no crash)", 1);
    ft_lstadd_back(&list, NULL); // Should not crash / change list
    print_test_result("lstadd_back with NULL new node (no change)", ft_lstsize(list) == 3 && ft_lstlast(list) == node3);
    ft_lstclear(&list, del_int_content);

    // ft_lstdelone
    printf("\nTesting ft_lstdelone...\n");
    // Case 1: Delete single node
    content1 = create_int_ptr(55);
    node1 = ft_lstnew(content1);
    ft_lstdelone(node1, del_int_content); // Deletes node and frees content
    // We can't reliably check memory after free, just test it doesn't crash
    print_test_result("lstdelone single node (no crash)", 1);

    // Case 2: Use in ft_lstclear (implicitly tested below)
    // Test with NULL delete function (should still free node)
    content1 = create_int_ptr(66);
    node1 = ft_lstnew(content1);
    ft_lstdelone(node1, NULL); // Should free node1 but not content1
    print_test_result("lstdelone with NULL del func (no crash)", 1);
    // We need to free the content manually now
    free(content1);

    // Test with NULL node (should not crash)
    ft_lstdelone(NULL, del_int_content);
    print_test_result("lstdelone with NULL node (no crash)", 1);

    // ft_lstclear
    printf("\nTesting ft_lstclear...\n");
    list = NULL;
    node1 = ft_lstnew(create_int_ptr(1));
    node2 = ft_lstnew(create_int_ptr(2));
    node3 = ft_lstnew(create_int_ptr(3));
    ft_lstadd_front(&list, node3); // List: 3 -> NULL
    ft_lstadd_front(&list, node2); // List: 2 -> 3 -> NULL
    ft_lstadd_front(&list, node1); // List: 1 -> 2 -> 3 -> NULL
    list_size = ft_lstsize(list);
    print_test_result("lstclear setup (size is 3)", list_size == 3);
    ft_lstclear(&list, del_int_content);
    print_test_result("lstclear list is NULL after clear", list == NULL);
    // Test clearing an already empty list
    ft_lstclear(&list, del_int_content);
    print_test_result("lstclear empty list (no crash)", 1);
    // Test clearing with NULL del function
    list = ft_lstnew(create_int_ptr(10)); // Content needs manual free later
    content1 = list->content;             // Save pointer to manually free
    ft_lstclear(&list, NULL);
    print_test_result("lstclear with NULL del func (list is NULL)", list == NULL);
    print_test_result("lstclear with NULL del func (no crash)", 1);
    free(content1); // Manually free content
    // Test clearing with NULL list pointer
    ft_lstclear(NULL, del_int_content);
    print_test_result("lstclear with NULL list pointer (no crash)", 1);

    // ft_lstiter
    printf("\nTesting ft_lstiter...\n");
    list = NULL;
    node1 = ft_lstnew(create_int_ptr(10));
    node2 = ft_lstnew(create_int_ptr(20));
    node3 = ft_lstnew(create_int_ptr(30));
    ft_lstadd_back(&list, node1);
    ft_lstadd_back(&list, node2);
    ft_lstadd_back(&list, node3);
    ft_lstiter(list, iter_increment_int);
    print_test_result("lstiter first element updated", list && *(int *)list->content == 11);
    print_test_result("lstiter second element updated", list && list->next && *(int *)list->next->content == 21);
    print_test_result("lstiter third element updated", list && list->next && list->next->next && *(int *)list->next->next->content == 31);
    // Test with empty list
    t_list *empty_list = NULL;
    ft_lstiter(empty_list, iter_increment_int);
    print_test_result("lstiter empty list (no crash)", 1);
    // Test with NULL function
    ft_lstiter(list, NULL); // Should not crash or change values
    print_test_result("lstiter NULL function (no crash)", 1);
    print_test_result("lstiter NULL function (values unchanged)", list && *(int *)list->content == 11 && list->next && *(int *)list->next->content == 21 && list->next->next && *(int *)list->next->next->content == 31);
    ft_lstclear(&list, del_int_content);

    // ft_lstmap
    printf("\nTesting ft_lstmap...\n");
    list = NULL;
    node1 = ft_lstnew(create_int_ptr(5));
    node2 = ft_lstnew(create_int_ptr(15));
    ft_lstadd_back(&list, node1);
    ft_lstadd_back(&list, node2);
    mapped_list = ft_lstmap(list, map_increment_int, del_int_content);
    print_test_result("lstmap new list created", mapped_list != NULL && mapped_list != list);
    print_test_result("lstmap size is correct", ft_lstsize(mapped_list) == 2);
    print_test_result("lstmap first element content correct", mapped_list && mapped_list->content && *(int *)mapped_list->content == 6);
    print_test_result("lstmap second element content correct", mapped_list && mapped_list->next && mapped_list->next->content && *(int *)mapped_list->next->content == 16);
    print_test_result("lstmap original list unchanged", list && *(int *)list->content == 5 && list->next && *(int *)list->next->content == 15);
    ft_lstclear(&list, del_int_content);        // Clear original list
    ft_lstclear(&mapped_list, del_int_content); // Clear mapped list

    // Test map with empty list
    list = NULL;
    mapped_list = ft_lstmap(list, map_increment_int, del_int_content);
    print_test_result("lstmap empty list input (result is NULL)", mapped_list == NULL);
    ft_lstclear(&mapped_list, del_int_content); // Should do nothing, but good practice

    // Test map with NULL function
    list = ft_lstnew(create_int_ptr(1));
    mapped_list = ft_lstmap(list, NULL, del_int_content);
    print_test_result("lstmap NULL function (result is NULL)", mapped_list == NULL);
    ft_lstclear(&list, del_int_content); // Original list still needs clearing

    // Test map with NULL delete function (should still work)
    list = ft_lstnew(create_int_ptr(10));
    mapped_list = ft_lstmap(list, map_increment_int, NULL);
    print_test_result("lstmap NULL delete func (list created)", mapped_list != NULL);
    print_test_result("lstmap NULL delete func (content correct)", mapped_list && mapped_list->content && *(int *)mapped_list->content == 11);
    // Need to manually clean up content if del is NULL
    if (mapped_list)
        free(mapped_list->content);
    ft_lstclear(&mapped_list, NULL);     // Use NULL del as content is freed
    ft_lstclear(&list, del_int_content); // Clear original

    // Test map where mapping function fails (returns NULL)
    list = ft_lstnew(create_int_ptr(1));                 // First node maps ok
    ft_lstadd_back(&list, ft_lstnew(NULL));              // Second node map_increment_int will return NULL
    ft_lstadd_back(&list, ft_lstnew(create_int_ptr(2))); // Third node maps ok
    mapped_list = ft_lstmap(list, map_increment_int, del_int_content);
    print_test_result("lstmap map func fails (result is NULL)", mapped_list == NULL);
    // Original list content needs clearing (including the NULL content node)
    ft_lstdelone(list->next, NULL);      // Delete the node with NULL content (don't call del)
    list->next = list->next->next;       // Relink list
    ft_lstclear(&list, del_int_content); // Clear remaining nodes

    printf("\n\n--- Testing Complete ---\n");

    // Print failed tests if any
    if (g_tests_failed > 0)
    {
        printf("\n--- Failed Tests (%d) ---\n", g_tests_failed);
        for (int i = 0; i < g_failed_test_count; i++)
        {
            printf("  - %s\n", g_failed_test_names[i]);
        }
        if (g_failed_list_full_warning_shown)
        {
            printf("  ... (list truncated at %d entries)\n", MAX_FAILS);
        }
    }

    // Add summary stats
    float pass_percentage = (g_total_tests > 0) ? ((float)g_tests_passed / g_total_tests) * 100 : 0;
    printf("\n--- Test Summary ---\n");
    printf("Total tests: %d\n", g_total_tests);
    printf("Passed: %d (%.2f%%)\n", g_tests_passed, pass_percentage);
    printf("Failed: %d (%.2f%%)\n", g_tests_failed, 100.0 - pass_percentage);

    return (0);
}