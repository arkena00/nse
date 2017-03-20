#ifndef NSE_ENCODER_H_NSE
#define NSE_ENCODER_H_NSE

namespace nse
{
    namespace encoders { class global; }

    class encoder
    {
    public:
        template<class Encoder = encoders::global, class Linear_type, class T>
        static void decode(const Linear_type& in, T& out);

        template<class T, class Encoder = encoders::global, size_t Version = 1, class Linear_type>
        static T decode(const Linear_type& in);
        template<class T, class Encoder = encoders::global, size_t Version = 1, class Linear_type>
        static T decode(Linear_type* in);

        template<class Encoder = encoders::global, class T, class Linear_type>
        static void encode(const T& in, Linear_type& out);

        template<class Linear_type, class Encoder = encoders::global, size_t Version = 1, class T>
        static Linear_type encode(const T& in);
    };

     // encoding
    template<class Linear_type, class Encoder, size_t Version = 1, class T>
    Linear_type encoder::encode(const T& in)
    {
        return reinterpret_cast<const char*>(in);
    }

    template<> const char* encoder::encode<const char*>(const std::string& v);
} // nse

#endif // NSE_ENCODER_H_NSE
