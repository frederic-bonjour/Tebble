#ifndef SINGLETONTPL_H
#define SINGLETONTPL_H

template <class T> class Singleton {
    public:
        static T& get() noexcept {
            return m_i;
        }

    protected:
        static T m_i;

    private:
        T& operator= (const T&){}
};

template <class T> T Singleton<T>::m_i = T();

#endif