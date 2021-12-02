// Include
#include "DxLib.h"

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(true);

    // ��ʉ𑜓x�̎w��
    SetGraphMode(1280, 720, 32);

    // DX���C�u�����̏�����
    if (DxLib_Init() == -1) return 0;

    // �w�i�F�̕ύX
    SetBackgroundColor(50, 50, 50);

    // ����ʂɕ`�悷��
    SetDrawScreen(DX_SCREEN_BACK);

    // ���C�g����
    SetUseLighting(false);

    // Z�o�b�t�@�L��
    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);

    // �J�������W�ƒ����_�̐ݒ�
    SetCameraPositionAndTarget_UpVecY(VGet(3.0f, 5.0f, -40.0f), VGet(0.0f, 0.0f, 0.0f));

    // NEAR��FAR�̐ݒ�
    SetCameraNearFar(1.0f, 100.0f);

    // ���_�f�[�^�̒�`
    VERTEX3D v[8] = { 0 };

    v[0].pos = VGet(-0.5f,  0.5f, -0.5f);
    v[1].pos = VGet( 0.5f,  0.5f, -0.5f);
    v[2].pos = VGet(-0.5f, -0.5f, -0.5f);
    v[3].pos = VGet( 0.5f, -0.5f, -0.5f);
    v[4].pos = VGet(-0.5f,  0.5f,  0.5f);
    v[5].pos = VGet( 0.5f,  0.5f,  0.5f);
    v[6].pos = VGet(-0.5f, -0.5f,  0.5f);
    v[7].pos = VGet( 0.5f, -0.5f,  0.5f);

    v[0].dif = GetColorU8(255, 0, 0, 255);
    v[1].dif = GetColorU8(0, 255, 0, 255);
    v[2].dif = GetColorU8(0, 0, 255, 255);
    v[3].dif = GetColorU8(255, 255, 0, 255);
    v[4].dif = GetColorU8(255, 0, 255, 255);
    v[5].dif = GetColorU8(0, 255, 255, 255);
    v[6].dif = GetColorU8(0, 0, 0, 255);
    v[7].dif = GetColorU8(255, 255, 255, 255);

    // �C���f�N�X�z���錾
    unsigned short index[] =
    {
        0,1,2,
        1,3,2,
        0,4,5,
        0,5,1,
        1,5,3,
        5,7,3,
        4,0,2,
        4,2,6,
        4,5,6,
        5,7,6,
        6,7,2,
        2,7,3
    };

    float x = 0.0f, y = 0.0f, z = 0.0f;

    float move = 0.0f;
    bool check = false;

    // ���C�����[�v
    while (ProcessMessage() != -1 && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
       /* x += 0.5f;
        y += 0.5f;
        z += 0.5f;*/

        if (CheckHitKey(KEY_INPUT_SPACE)) { check = true; }

        if (check) { move -= 1.0f; }

        // ��ʏ�����
        ClearDrawScreen();

        // ��]�s��̍쐬
        MATRIX world = MGetRotX(x * DX_PI_F / 180.0f);
        world = MMult(world, MGetRotY(y * DX_PI_F / 180.0f));
        world = MMult(world, MGetRotZ(z * DX_PI_F / 180.0f));

        // �쐬�������[���h�s���K�p
        SetTransformToWorld(&world);

        for (float i = 0.0f; i < 8.0f; i+=2.0f)
        {
            for (float j = 0.0f; j < 8.0f; j += 2.0f)
            {
                for (float k = 0.0f;k < 8.0f; k += 2.0f)
                {
                    // ���_�f�[�^�̒�`
                    VERTEX3D v2[8] = { 0 };

                    v2[0].pos = VGet(-0.5f+i, 0.5f+j, -0.5f+k+move);
                    v2[1].pos = VGet(0.5f+i, 0.5f+j, -0.5f+k + move);
                    v2[2].pos = VGet(-0.5f+i, -0.5f+j, -0.5f+k + move);
                    v2[3].pos = VGet(0.5f+i, -0.5f+j, -0.5f+k + move);
                    v2[4].pos = VGet(-0.5f+i, 0.5f+j, 0.5f+k + move);
                    v2[5].pos = VGet(0.5f+i, 0.5f+j, 0.5f+k + move);
                    v2[6].pos = VGet(-0.5f+i, -0.5f+j, 0.5f+k + move);
                    v2[7].pos = VGet(0.5f+i, -0.5f+j, 0.5f+k + move);

                    v2[0].dif = GetColorU8(102, 255, 102, 255);
                    v2[1].dif = GetColorU8(102, 255, 102, 255);
                    v2[2].dif = GetColorU8(102, 255, 102, 255);
                    v2[3].dif = GetColorU8(102, 255, 102, 255);
                    v2[4].dif = GetColorU8(102, 255, 102, 255);
                    v2[5].dif = GetColorU8(102, 255, 102, 255);
                    v2[6].dif = GetColorU8(102, 255, 102, 255);
                    v2[7].dif = GetColorU8(102, 255, 102, 255);

                    // �C���f�b�N�X�o�b�t�@���g���ă|���S���̕`��
                    DrawPolygonIndexed3D(v2, 8, index, 12, DX_NONE_GRAPH, false);

                }
            }
        }

        // ����ʂɕ`�悵�����e��\�ɕ\������
        ScreenFlip();
    }

    // DX���C�u�����̔j��
    DxLib_End();

    return 0;
}