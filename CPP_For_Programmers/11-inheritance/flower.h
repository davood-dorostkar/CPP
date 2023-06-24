#ifndef FLOWER_H
#define FLOWER_H
#include <string>

class Flower
{
    std::string bloomTime;
public:
    Flower() {}
    std::string getBloom();
    void setBloom(std::string bloom);
};

std::string Flower::getBloom()
{
    return  bloomTime;
}

void Flower::setBloom(std::string bloom)
{
    bloomTime = bloom;
}
class Rose : public Flower
{
    std::string fragrance;
public:
    Rose() {}
    std::string getFragrance();
    void setFragrance(std::string frag);
};

std::string Rose::getFragrance()
{
    return fragrance;
}
void Rose::setFragrance(std::string frag)
{
    fragrance = frag;
}

#endif // FLOWER_H
