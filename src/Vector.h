#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <algorithm>

template <typename Object>
class Vector
{
private:
    int theSize;
    int theCapacity;
    Object *objects;

public:
    static const int SPARE_CAPACITY = 16;

   /**
    *   Default Constructor
    *   Uses initialization list to initialize theSize and theCapacity
    *   Declared as explicit to avoid implicit type conversion
    */
    explicit Vector( int initSize = 0 ): theSize{ initSize } , theCapacity{ initSize + SPARE_CAPACITY }
    {
        objects = new Object[ theCapacity ];
    }

   /**
    *   One-parameter Constructor or Copy Constructor
    *   Uses initialization list as much as possible to initialize member variables
    *   objects is first assigned to nullptr and then memory is allocated for it
    */
    Vector( const Vector & rhs ): theSize{ rhs.theSize } , theCapacity{ rhs.theCapacity } , objects{ nullptr }
    {

        objects = new Object [ theCapacity ];

        for( int i = 0 ; i < theSize ; ++ i ) {
            objects[i] = rhs.objects[i];
        }
    }

   /**
    *   Copy Assignment operator
    */
    Vector & operator= ( const Vector &rhs )
    {
        Vector copy = rhs;
        std::swap( *this , copy );
        return *this;
    }

   /**
    *   Destructor
    */
    ~Vector()
    {
        delete [] objects;
    }

   /**
    *   Move Constructor
    */
    Vector( Vector &&rhs ): theSize{ rhs.theSize } , theCapacity{ rhs.theCapacity } , objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

   /**
    *   Move Assignment
    */
    Vector & operator= ( Vector &&rhs )
    {
        std::swap( theSize , rhs.theSize );
        std::swap( theCapacity , rhs.theCapacity );
        std::swap( objects , rhs.objects );

        return *this;
    }

   /**
    *   Changes the size of vector.
    *   If the provided size is larger than the current Capacity, reserve 2x the size
    */
    void resize( int newSize )
    {
        if( newSize > theCapacity ) {
            reserve( newSize * 2 );
        }

        theSize = newSize;
    }

   /**
    *   Reserve extra memory space for the objects container
    */
    void reserve( int newCapacity )
    {
        if( newCapacity < theSize ) {
            return;
        }

        Object *newArray = new Object[ newCapacity ];

        for( int i = 0 ; i < theSize ; ++ i ) {
            newArray[i] = std::move( objects[i] );
        }

        theCapacity = newCapacity;
        std::swap( objects , newArray );
        delete [] newArray;
    }

   /**
    *   Subscript Operator
    */
    Object & operator[] ( int index )
    {
        return objects[index];
    }

   /**
    *   Const Subscript Operator
    */
    const Object & operator[] ( int index ) const
    {
        return objects[index];
    }

   /**
    *   Checks whether the container is empty
    */
    bool empty() const
    {
        return size() == 0;
    }

   /**
    *   Return theSize
    */
    int size() const
    {
        return theSize;
    }

   /**
    *   Return theCapacity
    */
    int capacity() const
    {
        return theCapacity;
    }

   /**
    *   Add element at the end (r-value)
    */
    void push_back( const Object &x )
    {
        if( theSize == theCapacity ) {
            reserve( 2 * theCapacity + 1 );
        }

        objects[theSize ++] = x;
    }

   /**
    *   Add element at the end (l-value)
    */
    void push_back( Object &&x )
    {
        if( theSize == theCapacity ) {
            reserve( 2 * theCapacity + 1 );
        }

        objects[theSize ++] = std::move( x );
    }

   /**
    *   Remove last element in the array
    */
    void pop_back()
    {
        theSize --;
    }

    const Object & back() const
    {
        return objects[theSize - 1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
    {
        return &objects[0];
    }

    const_iterator begin() const
    {
        return &objects[0];
    }

    iterator end()
    {
        return &objects[size()];
    }
    const_iterator end() const
    {
        return &objects[size()];
    }
};

#endif // VECTOR_H_INCLUDED
