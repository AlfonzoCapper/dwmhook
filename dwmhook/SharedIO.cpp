#include "SharedIO.h"

SharedIO::SharedIO()
{
	//��ʼ�������ڴ� ӳ�䵽�ڴ浱����
	hmap_ = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL,
		PAGE_READWRITE | SEC_COMMIT, 0, SHARED_SIZE, "eli");

	if (hmap_ == NULL)
	{
		return;
	}

	lpdata_ = MapViewOfFile(hmap_, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
}

SharedIO::~SharedIO()
{

}

bool SharedIO::InitSharedMem()
{
	if (lpdata_ == NULL)
	{
		return false;
	}

	shared_mem_ = (SharedMem*)lpdata_;
	return true;
}
