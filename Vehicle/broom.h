#ifndef BROOM_H
#define BROOM_H

namespace vehicle
{
    class Broom : public vehicle::Air_Vehicle
    {
    public:
        Broom();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // BROOM_H
