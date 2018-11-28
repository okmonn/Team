#pragma once
#include "../etc/tString.h"
#include <map>
#include <vector>
#include <memory>

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
struct ID3D12RootSignature;
struct ID3D12PipelineState;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
class Device;
class Queue;
class List;
class Fence;
class Root;
class Pipe;

class Effector
{
	struct Info {
		//���\�[�X
		ID3D12Resource* rsc;
		//���M�f�[�^
		float* data;
		//�ԍ�
		int index;
	};

	// �p�����[�^
	struct Param {
		//������
		float attenuation;
		//�x������
		float time;
		//���[�v��
		int loop;
		//�S�̂̔g�`������̑��ΐ�
		unsigned int index;
		//�T���v�����O���g��
		int sample;
	};

public:
	// �R���X�g���N�^
	Effector(std::weak_ptr<Device>dev, const std::tstring& fileName);
	// �f�X�g���N�^
	~Effector();

	// �p�����[�^�̃Z�b�g
	void SetParam(const float& attenuation, const float& time, const int& loop, const unsigned int& index, const int& sample = 44100) {
		param = { attenuation, time, loop, index, sample };
	}

	// ���s
	void Execution(const std::vector<float>& wave, std::vector<float>& adaptation, const unsigned int& index, const unsigned int& sample = 44100);

private:
	// ���[�g�V�O�l�`���̐���
	long CreateRoot(const std::tstring& fileName);

	// �p�C�v���C���̐���
	long CreatePipe(void);

	// �q�[�v�̐���
	long CreateHeap(void);

	// CBV���\�[�X�̐���
	long CreateCbvRsc(const std::string& name, const unsigned int& size);

	// UAV���\�[�X�̐���
	long CreateUavRsc(const std::string& name, const unsigned int& size);

	// CBV�̐���
	void CreateConstantView(const std::string& name, const unsigned int& size);

	// UAV�̐���
	void CreateUnorderView(const std::string& name, const unsigned int& stride, const unsigned int& num);

	// �}�b�v
	long Map(const std::string& name);

	// CBV�̐���
	void CBV(const std::string& name, const unsigned int& size);

	// UAV�̐���
	void UAV(const std::string& name, const unsigned int& stride, const unsigned int& num);

	// ������
	void Init(void);


	// �f�o�C�X
	std::weak_ptr<Device>dev;

	// �L���[
	std::shared_ptr<Queue>queue;

	// ���X�g
	std::unique_ptr<List>list;

	// �t�F���X
	std::unique_ptr<Fence>fence;

	// ���[�g�V�O�l�`��
	ID3D12RootSignature* root;

	// �V�F�[�_�[���
	ID3DBlob* shader;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X�ԍ�
	int index;

	// �p�����[�^
	Param param;

	// �o�b�t�@
	std::map<std::string, Info>info;
};
