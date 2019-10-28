#pragma once
#include "cScene.h"
class cLoadScene : public cScene
{
private:
	int m_NowLoad;
	int m_MaxLoad;
	int m_NowSoundLoad;
	int m_MaxSoundLoad;
	struct strBun
	{
		string key;
		string path;
		int count = 0;
		strBun(const string& key, const string& path, int count = 0)
			:key(key), path(path), count(count) {};
	};
	struct strBunSound
	{
		string key;
		wstring path;
		int count = 0;
		strBunSound(const string& key, const wstring& path)
			:key(key), path(path) {};
	};

	vector<strBun> m_Load;
	vector<strBunSound> m_SoundLoad;

	void Load(const string& key, const string& path, int count = 0) {
		m_Load.push_back(strBun(key, path, count));
	}
	void SoundLoad(const string& key, const wstring& path) {
		m_SoundLoad.push_back(strBunSound(key, path));
	}
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
