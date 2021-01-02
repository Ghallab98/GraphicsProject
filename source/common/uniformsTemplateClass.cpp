enum uniformType
{
    tint,
    texture,
    sampler
}; //to be filled with all the values we could possibly have INBETWEEN THE VALUES NOT THE FIRST NOR THE LAST
template <class T>

class Uniform
{
private:
    uniformType type; //could be tint for example
    T value;          //could be vec4
public:
    Uniform(uniformType sentType, T sentVal)
    {
        if (sentType >= tint && sentType <= sampler) ///check if the sentType is in the enum list
        {
            type = sentType;
            value = sentVal;
            return 1;
        }
        return -1;
    }
    uniformType getUniformtype()
    {
        return this->type;
    }
    T getUniformValue()
    {
        return this->value;
    }
};