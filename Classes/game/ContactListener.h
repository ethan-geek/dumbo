#if !defined(MS_648FD14BC_6020_4715_83E71_4E7232FF035E__INCLUDED_)
#define MS_648FD14BC_6020_4715_83E71_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../game/Hero.h"

class ContactListener :	public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private :
	AGApplication* _application;
};

#endif // !defined(MS_648FD14BC_6020_4715_83E71_4E7232FF035E__INCLUDED_)