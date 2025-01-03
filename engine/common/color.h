#pragma once

template <typename T>
struct ColorT
{
  T r;
  T g;
  T b;
  T a;

  explicit ColorT() : r(0), g(0), b(0), a(1) {}
  explicit ColorT(unsigned int packed)
  {
    a = static_cast<float>((packed >> 24) / 255.0f);
    b = static_cast<float>(((packed << 8) >> 24) / 255.0f);
    g = static_cast<float>(((packed << 16) >> 24) / 255.0f);
    r = static_cast<float>(((packed << 24) >> 24) / 255.0f);
  }

  bool operator==(const ColorT<T> &other) const
  {
    return (r == other.r && g == other.g && b == other.b && a == other.a);
  }
};

typedef ColorT<float> Colorf;

static inline const Colorf TransparentBlack{0x00000000};
static inline const Colorf Transparent{0x00000000};
static inline const Colorf AliceBlue{0xfffff8f0};
static inline const Colorf AntiqueWhite{0xffd7ebfa};
static inline const Colorf Aqua{0xffffff00};
static inline const Colorf Aquamarine{0xffd4ff7f};
static inline const Colorf Azure{0xfffffff0};
static inline const Colorf Beige{0xffdcf5f5};
static inline const Colorf Bisque{0xffc4e4ff};
static inline const Colorf Black{0xff000000};
static inline const Colorf BlanchedAlmond{0xffcdebff};
static inline const Colorf Blue{0xffff0000};
static inline const Colorf BlueViolet{0xffe22b8a};
static inline const Colorf Brown{0xff2a2aa5};
static inline const Colorf BurlyWood{0xff87b8de};
static inline const Colorf CadetBlue{0xffa09e5f};
static inline const Colorf Chartreuse{0xff00ff7f};
static inline const Colorf Chocolate{0xff1e69d2};
static inline const Colorf Coral{0xff507fff};
static inline const Colorf CornflowerBlue{0xffed9564};
static inline const Colorf Cornsilk{0xffdcf8ff};
static inline const Colorf Crimson{0xff3c14dc};
static inline const Colorf Cyan{0xffffff00};
static inline const Colorf DarkBlue{0xff8b0000};
static inline const Colorf DarkCyan{0xff8b8b00};
static inline const Colorf DarkGoldenrod{0xff0b86b8};
static inline const Colorf DarkGray{0xffa9a9a9};
static inline const Colorf DarkGreen{0xff006400};
static inline const Colorf DarkKhaki{0xff6bb7bd};
static inline const Colorf DarkMagenta{0xff8b008b};
static inline const Colorf DarkOliveGreen{0xff2f6b55};
static inline const Colorf DarkOrange{0xff008cff};
static inline const Colorf DarkOrchid{0xffcc3299};
static inline const Colorf DarkRed{0xff00008b};
static inline const Colorf DarkSalmon{0xff7a96e9};
static inline const Colorf DarkSeaGreen{0xff8bbc8f};
static inline const Colorf DarkSlateBlue{0xff8b3d48};
static inline const Colorf DarkSlateGray{0xff4f4f2f};
static inline const Colorf DarkTurquoise{0xffd1ce00};
static inline const Colorf DarkViolet{0xffd30094};
static inline const Colorf DeepPink{0xff9314ff};
static inline const Colorf DeepSkyBlue{0xffffbf00};
static inline const Colorf DimGray{0xff696969};
static inline const Colorf DodgerBlue{0xffff901e};
static inline const Colorf Firebrick{0xff2222b2};
static inline const Colorf FloralWhite{0xfff0faff};
static inline const Colorf ForestGreen{0xff228b22};
static inline const Colorf Fuchsia{0xffff00ff};
static inline const Colorf Gainsboro{0xffdcdcdc};
static inline const Colorf GhostWhite{0xfffff8f8};
static inline const Colorf Gold{0xff00d7ff};
static inline const Colorf Goldenrod{0xff20a5da};
static inline const Colorf Gray{0xff808080};
static inline const Colorf Green{0xff008000};
static inline const Colorf GreenYellow{0xff2fffad};
static inline const Colorf Honeydew{0xfff0fff0};
static inline const Colorf HotPink{0xffb469ff};
static inline const Colorf IndianRed{0xff5c5ccd};
static inline const Colorf Indigo{0xff82004b};
static inline const Colorf Ivory{0xfff0ffff};
static inline const Colorf Khaki{0xff8ce6f0};
static inline const Colorf Lavender{0xfffae6e6};
static inline const Colorf LavenderBlush{0xfff5f0ff};
static inline const Colorf LawnGreen{0xff00fc7c};
static inline const Colorf LemonChiffon{0xffcdfaff};
static inline const Colorf LightBlue{0xffe6d8ad};
static inline const Colorf LightCoral{0xff8080f0};
static inline const Colorf LightCyan{0xffffffe0};
static inline const Colorf LightGoldenrodYellow{0xffd2fafa};
static inline const Colorf LightGray{0xffd3d3d3};
static inline const Colorf LightGreen{0xff90ee90};
static inline const Colorf LightPink{0xffc1b6ff};
static inline const Colorf LightSalmon{0xff7aa0ff};
static inline const Colorf LightSeaGreen{0xffaab220};
static inline const Colorf LightSkyBlue{0xffface87};
static inline const Colorf LightSlateGray{0xff998877};
static inline const Colorf LightSteelBlue{0xffdec4b0};
static inline const Colorf LightYellow{0xffe0ffff};
static inline const Colorf Lime{0xff00ff00};
static inline const Colorf LimeGreen{0xff32cd32};
static inline const Colorf Linen{0xffe6f0fa};
static inline const Colorf Magenta{0xffff00ff};
static inline const Colorf Maroon{0xff000080};
static inline const Colorf MediumAquamarine{0xffaacd66};
static inline const Colorf MediumBlue{0xffcd0000};
static inline const Colorf MediumOrchid{0xffd355ba};
static inline const Colorf MediumPurple{0xffdb7093};
static inline const Colorf MediumSeaGreen{0xff71b33c};
static inline const Colorf MediumSlateBlue{0xffee687b};
static inline const Colorf MediumSpringGreen{0xff9afa00};
static inline const Colorf MediumTurquoise{0xffccd148};
static inline const Colorf MediumVioletRed{0xff8515c7};
static inline const Colorf MidnightBlue{0xff701919};
static inline const Colorf MintCream{0xfffafff5};
static inline const Colorf MistyRose{0xffe1e4ff};
static inline const Colorf Moccasin{0xffb5e4ff};
static inline const Colorf NavajoWhite{0xffaddeff};
static inline const Colorf Navy{0xff800000};
static inline const Colorf OldLace{0xffe6f5fd};
static inline const Colorf Olive{0xff008080};
static inline const Colorf OliveDrab{0xff238e6b};
static inline const Colorf Orange{0xff00a5ff};
static inline const Colorf OrangeRed{0xff0045ff};
static inline const Colorf Orchid{0xffd670da};
static inline const Colorf PaleGoldenrod{0xffaae8ee};
static inline const Colorf PaleGreen{0xff98fb98};
static inline const Colorf PaleTurquoise{0xffeeeeaf};
static inline const Colorf PaleVioletRed{0xff9370db};
static inline const Colorf PapayaWhip{0xffd5efff};
static inline const Colorf PeachPuff{0xffb9daff};
static inline const Colorf Peru{0xff3f85cd};
static inline const Colorf Pink{0xffcbc0ff};
static inline const Colorf Plum{0xffdda0dd};
static inline const Colorf PowderBlue{0xffe6e0b0};
static inline const Colorf Purple{0xff800080};
static inline const Colorf Red{0xff0000ff};
static inline const Colorf RosyBrown{0xff8f8fbc};
static inline const Colorf RoyalBlue{0xffe16941};
static inline const Colorf SaddleBrown{0xff13458b};
static inline const Colorf Salmon{0xff7280fa};
static inline const Colorf SandyBrown{0xff60a4f4};
static inline const Colorf SeaGreen{0xff578b2e};
static inline const Colorf SeaShell{0xffeef5ff};
static inline const Colorf Sienna{0xff2d52a0};
static inline const Colorf Silver{0xffc0c0c0};
static inline const Colorf SkyBlue{0xffebce87};
static inline const Colorf SlateBlue{0xffcd5a6a};
static inline const Colorf SlateGray{0xff908070};
static inline const Colorf Snow{0xfffafaff};
static inline const Colorf SpringGreen{0xff7fff00};
static inline const Colorf SteelBlue{0xffb48246};
static inline const Colorf Tan{0xff8cb4d2};
static inline const Colorf Teal{0xff808000};
static inline const Colorf Thistle{0xffd8bfd8};
static inline const Colorf Tomato{0xff4763ff};
static inline const Colorf Turquoise{0xffd0e040};
static inline const Colorf Violet{0xffee82ee};
static inline const Colorf Wheat{0xffb3def5};
static inline const Colorf White{0xffffffff};
static inline const Colorf WhiteSmoke{0xfff5f5f5};
static inline const Colorf Yellow{0xff00ffff};
static inline const Colorf YellowGreen{0xff32cd9a};