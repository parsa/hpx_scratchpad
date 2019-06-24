#include <hpx/hpx_main.hpp>

#include <hpx/include/components.hpp>
#include <hpx/lcos/broadcast.hpp>

#include "dbg.h"

#include <cstdint>
#include <vector>

struct tc1 : hpx::components::component_base<tc1>
{
    std::uint32_t f1()
    {
        return hpx::get_locality_id();
    }
    HPX_DEFINE_COMPONENT_ACTION(tc1, f1);
};
using tc1_t = hpx::components::component<tc1>;
HPX_REGISTER_COMPONENT(tc1_t, tc1_t);

using f1_action = tc1_t::f1_action;
HPX_REGISTER_BROADCAST_ACTION_DECLARATION(f1_action)
HPX_REGISTER_BROADCAST_ACTION(f1_action)

int main()
{
    hpx::id_type here = hpx::find_here();
    
    std::vector<hpx::id_type> components = hpx::new_<tc1[]>(here, 10).get();
    
    std::vector<std::uint32_t> f1_res;
    f1_res = hpx::lcos::broadcast<f1_action>(components).get();
    
    dbg(dbg(f1_res.size()) == dbg(components.size()));
    for (std::size_t i = 0; dbg(i) != f1_res.size(); ++i)
    {
        dbg(dbg(f1_res[i]) == dbg(hpx::naming::get_locality_id_from_id(components[i])));
    }

    return 0;
}