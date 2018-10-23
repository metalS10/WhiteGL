#include "BinarySearch.h"

int CBinarySearch::search(std::vector<int> VSort, int findValue)
{
	//現在検索中の数字(全体の中心)(intにしておくことで少数は切れる)
	int sorting = VSort.size() * 0.5f;
	//とりあえずループ
	while (true)
	{
		//現在検索中の中心より探す要素が大きければ
		if (VSort[sorting] < findValue)
		{
			printf("%d : Success!(sorting:%d < +:%d)\n", sorting, VSort[sorting], findValue);
			//1の場合半分を足しても+0なので
			if (sorting == 1)
			{
				sorting++;
			}
			else
			{
				//現在の中心から下を取り除き中心をとる(半分+)
				sorting += (VSort.size() - sorting) * 0.5f;
			}
			//もしvectorの最大要素位置なら検索に引っかからなかった場合エラー
			if (sorting == VSort.size() - 1 && findValue != VSort[sorting])
			{
				printf("///error///%d is nothing in VSort....\n", findValue);
				return -1;
			}
		}
		//現在検索中の中心より探す要素が小さければ
		else if (VSort[sorting] > findValue)
		{
			printf("%d : Success!(sorting:%d > findValue:%d)\n", sorting, VSort[sorting], findValue);
			//現在の中心から上を取り除き中心をとる(更に半分)
			sorting *= 0.5f;
			//もし0なら検索に引っかからなかった場合エラー
			if (sorting == 0 && findValue != VSort[sorting])
			{
				printf("///error///%d is nothing in VSort....\n", findValue);
				return -1;
			}
		}
		//現在検索中の位置がヒットすれば
		else if (VSort[sorting] == findValue)
		{
			printf("%d : Goodjob!!!(%d = %d)\n", sorting, VSort[sorting], findValue);
			return sorting;
		}
		//万が一
		else
		{
			printf("what the fuck!? this program has probrem!\n");
			return -1;

		}
	}
}