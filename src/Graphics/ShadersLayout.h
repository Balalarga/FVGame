#ifndef ShadersLayout_H
#define ShadersLayout_H

#include <vector>

struct ShadersLayoutItem
{
    enum class Type
    {
        None, Float, Int, UnsignedInt
    };

    ShadersLayoutItem();
    ShadersLayoutItem(unsigned count, Type type);

    void Setup(unsigned count, Type type);

    unsigned count;
    Type type;
    unsigned size;
};

class ShadersLayout
{
public:
    ShadersLayout() = default;
    ShadersLayout(const std::vector<ShadersLayoutItem>& items);

    static unsigned GetOpenglType(ShadersLayoutItem::Type type);

    void Add(ShadersLayoutItem::Type type, unsigned count);

    inline const std::vector<ShadersLayoutItem>& GetLayoutItems() const
    {
        return _layoutItems;
    }

    inline unsigned GetStride() const
    {
        return _stride;
    }

    inline unsigned GetWidth() const
    {
        return _width;
    }

    ShadersLayout& operator=(const ShadersLayout& oth);

private:
    std::vector<ShadersLayoutItem> _layoutItems;
    unsigned _stride = 0;
    unsigned _width = 0;
};

#endif // ShadersLayout_H
