#include "BinarySearch.h"

int CBinarySearch::search(std::vector<int> VSort, int findValue)
{
	//���݌������̐���(�S�̂̒��S)(int�ɂ��Ă������Ƃŏ����͐؂��)
	int sorting = VSort.size() * 0.5f;
	//�Ƃ肠�������[�v
	while (true)
	{
		//���݌������̒��S���T���v�f���傫�����
		if (VSort[sorting] < findValue)
		{
			printf("%d : Success!(sorting:%d < +:%d)\n", sorting, VSort[sorting], findValue);
			//1�̏ꍇ�����𑫂��Ă�+0�Ȃ̂�
			if (sorting == 1)
			{
				sorting++;
			}
			else
			{
				//���݂̒��S���牺����菜�����S���Ƃ�(����+)
				sorting += (VSort.size() - sorting) * 0.5f;
			}
			//����vector�̍ő�v�f�ʒu�Ȃ猟���Ɉ���������Ȃ������ꍇ�G���[
			if (sorting == VSort.size() - 1 && findValue != VSort[sorting])
			{
				printf("///error///%d is nothing in VSort....\n", findValue);
				return -1;
			}
		}
		//���݌������̒��S���T���v�f�����������
		else if (VSort[sorting] > findValue)
		{
			printf("%d : Success!(sorting:%d > findValue:%d)\n", sorting, VSort[sorting], findValue);
			//���݂̒��S��������菜�����S���Ƃ�(�X�ɔ���)
			sorting *= 0.5f;
			//����0�Ȃ猟���Ɉ���������Ȃ������ꍇ�G���[
			if (sorting == 0 && findValue != VSort[sorting])
			{
				printf("///error///%d is nothing in VSort....\n", findValue);
				return -1;
			}
		}
		//���݌������̈ʒu���q�b�g�����
		else if (VSort[sorting] == findValue)
		{
			printf("%d : Goodjob!!!(%d = %d)\n", sorting, VSort[sorting], findValue);
			return sorting;
		}
		//������
		else
		{
			printf("what the fuck!? this program has probrem!\n");
			return -1;

		}
	}
}