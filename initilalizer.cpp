#include "initilalizer.h"
initilalizer::initilalizer()
{
    user_info user;
    user.to_null ();
    user.name="cat";
    user.password="meow";
    user.id=0;

    dao_base::update_core (user,user);

}

