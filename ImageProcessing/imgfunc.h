#ifndef IMGFUNC_H
#define IMGFUNC_H
#include <stdio.h>
#include <stdlib.h>

/** �摜��ނ̎��ʎq */
enum { GRAY=1, RGB=2};


/** �F������ێ����邽�߂̍\���́@*/
typedef struct{
 unsigned char r;
 unsigned char g;
 unsigned char b;
} Color;


/** �摜��ێ����邽�߂̍\���́@*/
typedef struct{
 int imgtype; /*�摜��ނ̎��ʎq�BGray�܂���RGB*/
 unsigned int width; /* �摜�̕� */
 unsigned int height; /* �摜�̍��� */
 unsigned char *data; /*��f�l(unsigned char�^�܂���Color�^)�̈ꎟ�z��ւ̃|�C���^*/
} Image;


/**
 * �摜�����������邽�߂̊֐�
 * 
 * �摜�\���̂̊e�t�B�[���h��0�܂���NULL�ɐݒ�
 * 
 * @param img �摜�\���̂ւ̃|�C���^  
 */
void initImage(Image *img);


/**
 * �摜�̃��������J�����邽�߂̊֐�
 * 
 * @param img �摜�\���̂ւ̃|�C���^  
 */
void freeImage(Image *img);

/**
 * �摜��V�K�쐬���邽�߂̊֐�
 * 
 * �^����ꂽ�傫���Ǝ�ނɉ����ĕK�v�ȃ������ʂ��m�ۂ�����A������
 * ����ݒ肵���\���̂�Ԃ��֐��B
 * 
 * @param height
 * @param width
 * @param type
 * @return �������V�K�摜�ւ̃|�C���^�B���s��NULL�B
 */
Image newImage( unsigned int height, unsigned int width, int type);


/**
 * �摜�t�@�C������ǂݍ��ނ��߂̊֐�
 * 
 * �^����ꂽ���O�̃t�@�C����PGM�Ȃ̂�PPM�Ȃ̂��𔻕ʂ��A�t�@�C���̎��
 * �ɉ����ăO���[�X�P�[���摜�܂��̓J���[�摜���t�@�C������ǂݍ��݁A�摜��
 * �\���̂ɐݒ肷��B
 * 
 * @param filename �t�@�C�����̕�����ւ̃|�C���^
 * @param img �t�@�C�����̕�����ւ̃|�C���^
 * @return ������0 ���s��1 
 */
int loadImage(char *filename, Image *img);


/**
 * �摜��ۑ����邽�߂̊֐�
 * 
 * �^����ꂽ�摜����ނ̎��ʎq�ɉ�����PGM�܂���PPM�Ƃ��ĕۑ�����֐�
 *  * 
 * @param filename �t�@�C�����̕�����ւ̃|�C���^
 * @param img �t�@�C�����̕�����ւ̃|�C���^
 * @return ������0 ���s��1 
 */
int saveImage(char *filename, Image *img);


/**
 * �O���[�X�P�[���摜�̎w��ʒu�̉�f�l���擾���邽�߂̊֐�
 *  
 * @param j �c�����̈ʒu
 * @param i �������̈ʒu
 * @param img �摜�ւ̃|�C���^
 * @return ��f�l 
 */
unsigned char getPixelGray(int j, int i,Image *img);

/**
 * �O���[�X�P�[���摜�̎w��ʒu�̉�f�l��ݒ肷�邽�߂̊֐�
 *  
 * @param j �c�����̈ʒu
 * @param i �������̈ʒu
 * @param pix ��f�l
 * @param img �摜�ւ̃|�C���^
 */
void setPixelGray(int j,int i, unsigned char pix, Image *img);


/**
 * �J���[�摜�̎w��ʒu�̉�f�̐F���擾���邽�߂̊֐�
 *  
 * @param j �c�����̈ʒu
 * @param i �������̈ʒu
 * @param img �摜�ւ̃|�C���^
 * @return �F�̍\���� 
 */
Color getPixelRGB(int j,int i, Image *img);

/**
 * �J���[�摜�̎w��ʒu�̉�f�̐F��ݒ肷�邽�߂̊֐�
 *  
 * @param j �c�����̈ʒu
 * @param i �������̈ʒu
 * @param clr ��f�̐F
 * @param img �摜�ւ̃|�C���^
 */
void setPixelRGB(int j,int i, Color pix, Image *img);

#endif