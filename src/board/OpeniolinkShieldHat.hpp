#ifndef OPENIOLINK_OPENIOLINKSHIELDHAT_HPP
#define OPENIOLINK_OPENIOLINKSHIELDHAT_HPP

// DRAFT file witch class OpeniolinkShieldHat

#include "Max14819.hpp"

namespace openiolink
{

    class OpeniolinkShieldHat
    {
    public:
        // members not in initializer list: default initialization: https://en.cppreference.com/w/cpp/language/default_initialization
        OpeniolinkShieldHat(){};
        ~OpeniolinkShieldHat(){};

    protected:
        typedef Max14819<0> Chip0;
        typedef Max14819<1> Chip1;

    private:
        Chip0 mChip0;
        Chip1 mChip1;

        //static constexpr int mMaxPortCount = 4;
    };

} // namespace openiolink
#endif
