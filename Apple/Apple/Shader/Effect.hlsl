// ���[�g�V�O�l�`���̐錾
#define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT),"\
                    "DescriptorTable(CBV(b0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "DescriptorTable(UAV(u0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "DescriptorTable(UAV(u1, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), "\
                                    "visibility = SHADER_VISIBILITY_ALL),"\
                    "StaticSampler(s0, "\
                                  "filter = FILTER_MIN_MAG_MIP_LINEAR, "\
                                  "addressU = TEXTURE_ADDRESS_WRAP, "\
                                  "addressV = TEXTURE_ADDRESS_WRAP, "\
                                  "addressW = TEXTURE_ADDRESS_WRAP, "\
                                  "mipLodBias = 0.0f, "\
                                  "maxAnisotropy = 0, "\
                                  "comparisonFunc = COMPARISON_NEVER, "\
                                  "borderColor = STATIC_BORDER_COLOR_TRANSPARENT_BLACK, "\
                                  "minLOD = 0.0f, "\
                                  "maxLOD = 3.402823466e+38f, "\
                                  "space = 0, "\
                                  "visibility = SHADER_VISIBILITY_ALL)"

// �p�����[�^
cbuffer Param : register(b0)
{
    //������
    float attenuation;
    //�x������
    float time;
    //���[�v��
    int loop;
    //�S�̂̔g�`���̑��ΐ�
    uint waveIndex;
    //�T���v�����O���g��
    int sample;
};

// �K���O�f�[�^
RWStructuredBuffer<float> origin : register(u0);
// �K���f�[�^
RWStructuredBuffer<float> real : register(u1);

#define PI 3.14159265f

// �f�B���C
void Delay(uint index)
{
    real[index] = origin[index];
    uint2 size;
    origin.GetDimensions(size.x, size.y);

    uint num = size.x * waveIndex + index;

    for (int i = 1; i <= loop; ++i)
    {
        int m = (int) (num - i * (sample * time));

        real[index] += (m >= 0) ? pow(attenuation, i) * origin[index] : 0.0f;
    }
}

// �f�B�X�g�[�V����
void Distortion(uint index)
{
    //������
    float gain = 10.0f;
    //���ʃ��x��
    float level = 0.5f;

    real[index] = origin[index] * gain;
    
    //�N���b�s���O
    if(real[index] >= 0.0f)
    {
        real[index] = atan(real[index]) / (PI / 2.0f);
    }
    else if(real[index] < -0.0f)
    {
        real[index] = atan(real[index]) / (PI / 2.0f) * 0.1f;
    }

    //���ʒ���
    real[index] *= level;
}

// �R���v���b�T
void Compressor(uint index)
{
    //�������l
    float threshold = 0.2f;
    //���V�I
    float ratio = 1.0f / 10.0f;
    //������
    float gain = 1.0f / (threshold + (1.0f - threshold) * ratio);

    real[index] = origin[index];

    //�U���̈��k
    if (real[index] > threshold)
    {
        real[index] = threshold + (real[index] - threshold) * ratio;
    }
    else if (real[index] < -threshold)
    {
        real[index] = -threshold + (real[index] + threshold) * ratio;
    }
    
    real[index] *= gain;
}

// ���~�b�^
void Limiter(uint index)
{
    //�������l
    float threshold = 0.2f;
    //���V�I
    float ratio = 1.0f / 10.0f;

    real[index] = origin[index];

    //�U���̈��k
    if (real[index] > threshold)
    {
        real[index] = threshold;
    }
    else if (real[index] < -threshold)
    {
        real[index] = -threshold;
    }
}

// �n�j���O��
float Hanning(int index, uint size)
{
    return (size % 2 == 0) ?
    //����
    0.5f - 0.5f * cos(2.0f * PI * index / size) :
    //�
    0.5f - 0.5f * cos(2.0f * PI * (index + 0.5f) / size);
}

// �V���N�֐�
float Sinc(float index)
{
    return (index == 0.0f) ? 1.0f : sin(index) / index;
}

// FIR���[�p�X�t�B���^
void FIR_LPF(uint index)
{
    //�G�b�W���g��
    float edge = 1000.0f / sample;
    //�J�ڑш敝
    float delta = 1000.0f / sample;
    //�x����̐�
    int num = (int) (3.1f / delta + 0.5f) - 1;
    if(num % 2 != 0)
    {
        ++num;
    }

    float data[32];
    int offset = num / 2;
    for (int i = -offset; i <= offset; ++i)
    {
        data[offset + i] = 2.0f * edge * Sinc(2.0f * PI * edge * i);
    }

    for (int n = 0; n <= num; ++n)
    {
        data[n] *= Hanning(n, num + 1);
        real[index] += (index - n >= 0) ? data[n] * origin[index - n] : 0.0f;
    }

    //�N���b�s���O
    if(real[index] > 1.0f)
    {
        real[index] = 1.0f;
    }
    else if(real[index] < -1.0f)
    {
        real[index] = -1.0f;
    }
}

// FIR�n�C�p�X�t�B���^
void FIR_HPF(uint index)
{
    //�G�b�W���g��
    float edge = 1000.0f / sample;
    //�J�ڑш敝
    float delta = 1000.0f / sample;
    //�x����̐�
    int num = (int) (3.1f / delta + 0.5f) - 1;
    if (num % 2 != 0)
    {
        ++num;
    }

    float data[32];
    int offset = num / 2;
    for (int i = -offset; i <= offset; ++i)
    {
        data[offset + i] = Sinc(PI * i) - 2.0f * edge * Sinc(2.0f * PI * edge * i);
    }

    for (int n = 0; n <= num; ++n)
    {
        data[n] *= Hanning(n, num + 1);
        real[index] += (index - n >= 0) ? data[n] * origin[index - n] : 0.0f;
    }

     //�N���b�s���O
    if (real[index] > 1.0f)
    {
        real[index] = 1.0f;
    }
    else if (real[index] < -1.0f)
    {
        real[index] = -1.0f;
    }
}

// �g������
void Tremolo(uint index)
{
    //�ϒ��[�x
    float depth = 0.5f;
    //�ϒ����g��
    float rate = 5.0f;

    //�ϒ��M��
    float signal = 1.0f + depth * sin((2.0f * PI * rate * index) / sample);

    real[index] = signal * origin[index];
}

// �r�u���[�g
void Vibrato(uint index)
{
     //�ϒ��[�x
    float depth = sample * 0.002f;
    //�ϒ����g��
    float rate = 5.0f;

    float tau = (sample * 0.002f) + depth * sin((2.0f * PI * rate * index) / sample);

    float t = (float) index - tau;
    int m = (int) t;
    float delta = t - (float) m;

    uint2 size;
    origin.GetDimensions(size.x, size.y);

    if (m >= 0 && m + 1 < size.x)
    {
        real[index] = delta * origin[m + 1] + (1.0f - delta) * origin[m];
    }
}

[RootSignature(RS)]
[numthreads(1, 1, 1)]
void CS(uint3 gID : SV_GroupID, uint3 gtID : SV_GroupThreadID, uint3 disID : SV_DispatchThreadID)
{
    Tremolo(gID.x);

    AllMemoryBarrierWithGroupSync();
}