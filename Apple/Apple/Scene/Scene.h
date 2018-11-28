
class Scene
{
public:
	virtual ~Scene() = 0;
private:
	virtual void Draw() = 0;
	virtual void Init() = 0;
};