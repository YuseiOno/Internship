#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* main */
int main(void) {
    time_t timer;
    struct tm *local;
    struct tm *utc;

    /* ���ݎ������擾 */
    timer = time(NULL);

    local = localtime(&timer); /* �n�����ɕϊ� */

    /* �n���� �ϊ���\�� 
    printf("�n����: ");
    printf("%4d/", local->tm_year + 1900);
    printf("%2d/", local->tm_mon + 1);
    printf("%2d ", local->tm_mday);
    printf("%2d:", local->tm_hour);
    printf("%2d:", local->tm_min);
    printf("%2d", local->tm_sec);
    printf(" %d\n", local->tm_isdst);

    utc = gmtime(&timer); /* ���萢�E��(UTC)�ɕϊ� */

    /* ���萢�E�� �ϊ���\�� 
    printf("���萢�E��: ");
    printf("%4d/", utc->tm_year + 1900);
    printf("%2d/", utc->tm_mon + 1);
    printf("%2d ", utc->tm_mday);
    printf("%2d:", utc->tm_hour);
    printf("%2d:", utc->tm_min);
    printf("%2d", utc->tm_sec);
    printf(" %d\n", utc->tm_isdst);

    return EXIT_SUCCESS;*/
}