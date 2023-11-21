#include "unicodeUtf8.h"
#include "common.h"

//����value����utf8�������ֽ���
uint32_t getByteNumOfEncodeUtf8(int value) {
    ASSERT(value > 0, "Can`t encode negative value!");

    // ����ascii�ַ���Ҫ1�ֽ�
    if (value <= 0x7f) {
        return 1;
    }

    //�˷�Χ����ֵ����Ϊutf8��Ҫ2�ֽ�
    if (value <= 0x7ff) {
        return 2;
    }

    //�˷�Χ����ֵ����Ϊutf8��Ҫ3�ֽ�
    if (value <= 0xffff) {
        return 3;
    }

    //�˷�Χ����ֵ����Ϊutf8��Ҫ4�ֽ�
    if (value <= 0x10ffff) {
        return 4;
    }

    return 0;  //������Χ����0
}

//��value����Ϊutf8��д�뻺����buf,����д����ֽ���
uint8_t encodeUtf8(uint8_t* buf, int value) {
    ASSERT(value > 0, "Can`t encode negative value!");

    //���մ���ֽ���д�뻺���� 
    if (value <= 0x7f) {   // ����ascii�ַ���Ҫ1�ֽ�
        *buf = value & 0x7f;
        return 1;
    }
    else if (value <= 0x7ff) {  //�˷�Χ����ֵ����Ϊutf8��Ҫ2�ֽ�
        //��д����ֽ�
        *buf++ = 0xc0 | ((value & 0x7c0) >> 6);
        // ��д����ֽ�
        *buf = 0x80 | (value & 0x3f);
        return 2;
    }
    else if (value <= 0xffff) { //�˷�Χ����ֵ����Ϊutf8��Ҫ3�ֽ�
        // ��д����ֽ� 
        *buf++ = 0xe0 | ((value & 0xf000) >> 12);
        //��д���м��ֽ�
        *buf++ = 0x80 | ((value & 0xfc0) >> 6);
        //���д����ֽ�
        *buf = 0x80 | (value & 0x3f);
        return 3;
    }
    else if (value <= 0x10ffff) { //�˷�Χ����ֵ����Ϊutf8��Ҫ4�ֽ�
        *buf++ = 0xf0 | ((value & 0x1c0000) >> 18);
        *buf++ = 0x80 | ((value & 0x3f000) >> 12);
        *buf++ = 0x80 | ((value & 0xfc0) >> 6);
        *buf = 0x80 | (value & 0x3f);
        return 4;
    }

    NOT_REACHED();
    return 0;
}

//���ؽ���utf8���ֽ���
uint32_t getByteNumOfDecodeUtf8(uint8_t byte) {
    //byteӦ����utf8�����1�ֽ�,���ָ����utf8�������ĵ��ֽڲ����򷵻�0
    if ((byte & 0xc0) == 0x80) {
        return 0;
    }

    if ((byte & 0xf8) == 0xf0) {
        return 4;
    }

    if ((byte & 0xf0) == 0xe0) {
        return 3;
    }

    if ((byte & 0xe0) == 0xc0) {
        return 2;
    }

    return 1;   //ascii��
}

//������bytePtrΪ��ʼ��ַ��UTF-8���� ����󳤶�Ϊlength ������UTF-8���оͷ���-1
int decodeUtf8(const uint8_t* bytePtr, uint32_t length) {
    //����1�ֽڵ�ascii:  0xxxxxxx
    if (*bytePtr <= 0x7f) {
        return *bytePtr;
    }

    int value;
    uint32_t remainingBytes;

    //�ȶ�ȡ��1�ֽ�
    //���ݸ��ֽڵĸ�nλ�ж���Ӧ�ֽ�����utf8����
    if ((*bytePtr & 0xe0) == 0xc0) {
        //����2�ֽڵ�utf8
        value = *bytePtr & 0x1f;
        remainingBytes = 1;
    }
    else if ((*bytePtr & 0xf0) == 0xe0) {
        //����3�ֽڵ�utf8
        value = *bytePtr & 0x0f;
        remainingBytes = 2;
    }
    else if ((*bytePtr & 0xf8) == 0xf0) {
        //����4�ֽڵ�utf8
        value = *bytePtr & 0x07;
        remainingBytes = 3;
    }
    else {   //�Ƿ�����
        return -1;
    }

    //���utf8��ն���˾Ͳ��ٶ���ȥ��
    if (remainingBytes > length - 1) {
        return -1;
    }

    //�ٶ�ȡ���ֽ��е�����
    while (remainingBytes > 0) {
        bytePtr++;
        remainingBytes--;
        //��2λ������10
        if ((*bytePtr & 0xc0) != 0x80) {
            return -1;
        }

        //�Ӵθ��ֽ������ֽ�,�����ۼӸ��ֽڵĵ�6λ
        value = value << 6 | (*bytePtr & 0x3f);
    }
    return value;
}
