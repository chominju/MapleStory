#pragma once

template<class T>
void Safe_Delete(T& object)
{
	if (object)
	{
		delete object; 
		object = nullptr; 
	}
}
