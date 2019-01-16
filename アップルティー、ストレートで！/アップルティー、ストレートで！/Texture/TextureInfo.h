#pragma once
#include <memory>
#include <DirectXMath.h>

struct D3D12_SUBRESOURCE_DATA;
struct ID3D12Resource;

namespace tex {
	// ���f�[�^
	struct Info {
		//���\�[�X
		ID3D12Resource* rsc;
		//�f�R�[�h
		std::unique_ptr<unsigned char[]>decode;
		//�T�u�f�[�^
		std::shared_ptr<D3D12_SUBRESOURCE_DATA>sub;
	};

	// ���_
	struct Vertex {
		//���W
		DirectX::XMFLOAT3 pos;
		//uv
		DirectX::XMFLOAT2 uv;
	};

	// �萔�o�b�t�@���
	struct CbvInfo {
		//�ړ��s��
		DirectX::XMFLOAT4X4 matrix;
		//uv���W
		DirectX::XMFLOAT2 uvPos;
		//uv�T�C�Y
		DirectX::XMFLOAT2 uvSize;
		//���]
		DirectX::XMFLOAT2 reverse;
		//�A���t�@�l
		float alpha;
	};
}
