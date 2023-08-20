#ifndef FLYING_CARPET_H
#define FLYING_CARPET_H

namespace vehicle
{
    class Flying_Carpet : public vehicle::Air_Vehicle
    {
    public:
        Flying_Carpet();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // FLYING_CARPET_H
