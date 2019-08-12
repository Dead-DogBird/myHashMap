#pragma once
#include <vector>

template<typename T>
class Key
{
public:
	Key()
	{

	}
	int index = -1;
	T key;//key값
	unsigned int hash;//key랑 연동시킬 해시값
	bool isAlready;
	void SetKey()///초기화
	{
		isAlready = false;
	}
	void SetKey(int Index, T Key, unsigned int Hash)
	{
		isAlready = true;
		index = Index;
		key = Key;
		hash = Hash;
	}
};
template<typename T>
void swap(T & t1, T & t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
template<typename keyType, typename valueType>
class HashMap
{
private:
	int MaxHash;
	std::vector<Key<keyType>> keys;
	std::vector<valueType> values;
	int valueindex;
public:
	HashMap(int Initsize) :keys(Initsize), values(Initsize), MaxHash(Initsize)
	{
		values.clear();
		valueindex = 0;
	}

	void Add(keyType key, valueType object)
	{
		//해쉬 생성 
		std::size_t hash = std::hash<keyType>()(key);
		//해쉬를 Index로 
		int index = hash % hashed;

		//values에 object를 넣어줌
		while (true)
		{
			if (valueindex > values.size())//values가 모자란다면
			{
				values.resize(values.size()*2);//2배로 늘려줌
				valueindex = 0;
				continue;
			}
			if (values[valueindex].empty)
			{
				values[valueindex] = object;	   
				break;
			}
			++valueindex;
		}

		//충돌이 일어났을때
		if (keys[index].isAlready)
		{
			MaxHash *= 2;//두배로 늘림

			keys.resize(MaxHash);//해시 사이즈로 리사이즈

			for (int i = 0; i < keys.size(); i++)
			{
				if (keys[i].isExist)//해시를 옮겨줌
				{
					int curIndex = keys[i].hash % hashed;//해시값이 두배로 늘어난 만큼 
					swaping<key<keyType>>(keys[curIndex], keys[i]);//다시 해시하여 옮겨줌
				}
			}
			index = hash % hashed;//해시해줌
		}
		keys[index].SetKey(valueindex, key, hash);//key에 넣어줌
	}
	valueType *Get(keyType key)
	{
		std::size_t hash = std::hash<keyType>()(key);
		int index = hash % MaxHash;
			return &values[keys[index].index];
	}
	void Delete(keyType key)//해시삭제
	{
		std::size_t hash = std::hash<keyType>()(key);
		int index = hash % MaxHash;
		values[keys[index].index].clear();
		keys[index].SetKey();
			return;
	}
};

