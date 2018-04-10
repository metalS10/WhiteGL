#pragma once
#include <string>
#include "../OpenAL/include/al.h"

class Audio
{
public:
	explicit Audio(const std::string& filePath);

	// ���[�v�ݒ�
	void Loop(const bool isLoop);

	// �Đ�
	void Play();

	// �ꎞ��~
	void Pause();

	// ��~
	void Stop();

	// �Đ������ǂ���
	const bool IsPlaying()const;

	// �����f�[�^�̎ڂ�b�P�ʂŎ擾����
	const float GetDuration()const;

	// ���݂̍Đ��ʒu��b�P�ʂŎ擾����
	const float GetOffset()const;

private:
	ALuint buffer;
	ALuint source;

};