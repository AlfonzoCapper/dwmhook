#pragma once
#include <windows.h>
#include "log.h"
template <typename T>
class VftableHook {


	T org_vftable;
	T new_vftable;
	T* pvftable;
	bool is_hook;



public:
	VftableHook(T t):VftableHook(){
		this->pvftable = t;
		
	}
	VftableHook() {
		this->org_vftable = NULL;
		this->new_vftable = NULL;
		this->pvftable = NULL;
		this->is_hook = false;
	}
	LPVOID Hook(uint32_t  num,T addr) {
		//vftableָ��ָ����ȷ�ڴ�鿪ʼHOOK
		LPVOID retaddr = NULL;
		if (this->is_hook) {
			return retaddr;
		}
		if (IsBadReadPtr((PVOID)*this->pvftable, 4096) == 0) {//�����ڴ渴��ԭ�������Ȼ���޸���ָ��ĵ�����α������
			this->org_vftable = *this->pvftable;
			this->new_vftable = (T) new BYTE[4096];
			
			memcpy(this->new_vftable, this->org_vftable, 4096);
			retaddr = *((T*)(this->new_vftable + num));
			*this->pvftable = this->new_vftable;
			*((T*)(this->new_vftable + num)) = addr;
			
			this->is_hook = true;
		}
		else
			AddToLog(0, XorStr("mem error 5"), 0, 0);

		return retaddr;
	}
	LPVOID Hook(T pvftable,uint32_t num, T addr) {
		this->pvftable = (T*)pvftable;
		return Hook(num, addr);

	}
	bool UnHook() {//�ͷſռ䲢��ԭָ������
		*this->pvftable = this->org_vftable;
		delete this->new_vftable;
		this->is_hook = false;
		return true;
	}
};
