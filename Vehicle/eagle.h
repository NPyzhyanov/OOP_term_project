#ifndef EAGLE_H
#define EAGLE_H

namespace vehicle
{
    class Eagle : public vehicle::Air_Vehicle
    {
    public:
        Eagle();
        
    private:
        double decrease_distance(double distance) override;
    };
}

#endif // EAGLE_H
