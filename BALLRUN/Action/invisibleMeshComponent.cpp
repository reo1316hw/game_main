#include "InvisibleMeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@param _skelton �X�P���g���f�[�^��p���邩�B
@sa SkeletalMeshComponent.h
*/
InvisibleMeshComponent::InvisibleMeshComponent(GameObject* _owner, bool _skelton)
	:Component(_owner)
	, mesh(nullptr)
	, textureIndex(0)
	, visible(true)
	, isSkelton(_skelton)
{
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddInvisibleMeshComponent(this);
}

InvisibleMeshComponent::~InvisibleMeshComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveInvisibleMeshComponent(this);
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void InvisibleMeshComponent::Draw(Shader* _shader)
{
	if (owner->GetState() != State::Dead)
	{
		if (mesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				owner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mesh->GetSpecPower());

			_shader->SetFloatUniform("uLuminance", mesh->GetLuminace());

			_shader->SetFloatUniform("uAlpha", mesh->GetAlpha());
			// Set the active texture

			// ���b�V���ɒ�`����Ă���e�N�X�`�����Z�b�g
			SetTextureToShader(_shader);

			// Set the argMesh's vertex array as active
			VertexArray* va = mesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void InvisibleMeshComponent::SetTextureToShader(Shader* shader)
{
	// ���b�V���e�N�X�`���Z�b�g
	int texID, stageCount = 0;
	texID = mesh->GetTextureID(TextureStage::DiffuseMap); // �f�B�t���[�Y
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mesh->GetTextureID(TextureStage::NormalMap); // �@���}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mesh->GetTextureID(TextureStage::SpecularMap); // �X�y�L�����[�}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mesh->GetTextureID(TextureStage::EmissiveMap); // ���ȕ��˃}�b�v
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}