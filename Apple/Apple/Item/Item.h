#pragma once

class Item {
public:
	//コンストラクタ
	Item();
	//デストラクタ
	~Item();
	// 
	int GetParm() { return parm; }
private:

	//アイテムを取得して変動する値
	float parm;
};