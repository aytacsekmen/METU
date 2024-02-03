#pragma once

#include "Iterable.tpp"

// Your implementations go here.



template<typename T>
class RepeatIterator : public IIterator<T>
{
private:
    //IIterator<T> *mSourceIterator; // Stores the ``source'' iterator which
        // will be used to iterate over the
        // elements of the source iterable to
        // which accumulate() was applied.
    T mRepeated;
    T mReturn; // Stores the accumulation. This is the last value
        // returned from next() for this iterator.

    bool mHasIterationStarted; // A flag indicating whether next() was
        // called on this iterator. mAccumulation is
        // valid only if this flag is true.

public:
    // A newly created ``source'' iterator is passed to this iterator's
    // constructor.
    RepeatIterator(T repeated)
        : //mReturn(sourceIterator),
        //mSourceIterator(sourceIterator),
        mRepeated(repeated),
        mHasIterationStarted(false)
    {
    }

    virtual T next()  override
    {
        if (!mHasIterationStarted)
        {
            // At first next(), we get the first element from the source
            // iterator and assign it as the accumulation.
            //mSourceIterator->next();
            mReturn=mRepeated;
            mHasIterationStarted = true;
        }
        else
        {
            // For further nexts, we pick the next element from the source
            // iterator and add it to the accumulation.
            //mSourceIterator->next();
            mReturn=mRepeated;
        }

        // The accumulation is returned to represent the next element of
        // this iterator.
        return mReturn;

        // If the source iterator throws a StopIteration exception during
        // the process, it is automatically received by our caller. We do
        // not need to create and throw a new StopIteration exception
        // ourselves. Further next() calls also have the same behavior.
    }

    //virtual ~RepeatIterator() override
    //{
    //    // We own the source iterator passed to us. We destroy it when we
    //    // ourselves are destroyed.
    //    //delete mSourceIterator;
    //}
};

template<typename T>
class RepeatIterable : public IIterable<T>
{
    private:
        //IIterable<T> *mSourceIterable;

        T repeated; // Stores the ``source'' iterable to
                                       // which accumulate() was applied to get
                                       // this iterable.
        
    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        RepeatIterable(T v1)
            : repeated(v1)
            
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
        return new RepeatIterator<T>(repeated);
        }
        
        //virtual ~RepeatIterable() override
        //{
        //    // We own the source iterable passed to us. We destroy it when we
        //     //ourselves are destroyed.
        //    delete mSourceIterable;
        //}
};


template<typename T>
class CountIterator : public IIterator<T>
{
    private:
        //IIterator<T> *mSourceIterator; 
        T mNumber1;
        T mNumber2;
        T mReturn;
        bool mHasIterationStarted; 
        
    public:

        CountIterator(T input1,T input2)
            : mNumber1(input1),
              mNumber2(input2),
              mReturn(),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next()  override
    {
        if (!mHasIterationStarted)
        {
            // At first next(), we get the first element from the source
            // iterator and assign it as the accumulation.
            //mSourceIterator->next();
            mReturn=mNumber1;
            mHasIterationStarted = true;
        }
        else
        {
            // For further nexts, we pick the next element from the source
            // iterator and add it to the accumulation.
            //mSourceIterator->next();
            mReturn+=mNumber2;
        }

        // The accumulation is returned to represent the next element of
        // this iterator.
        return mReturn;

        // If the source iterator throws a StopIteration exception during
        // the process, it is automatically received by our caller. We do
        // not need to create and throw a new StopIteration exception
        // ourselves. Further next() calls also have the same behavior.
    }
        
        //virtual ~CountIterator() override
        //{
        //    // We own the source iterator passed to us. We destroy it when we
        //    // ourselves are destroyed.
        //    delete mSourceIterator;
        //}
};


template<typename T>
class CountIterable : public IIterable<T>
{
    private:
        //IIterable<T> *mSourceIterable; // Stores the ``source'' iterable to
                                       // which accumulate() was applied to get
                                       // this iterable.
        T mNumber1;
        T mNumber2;
    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        CountIterable(T input1, T input2)
            : mNumber1(input1),
              mNumber2(input2)
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
            return new CountIterator<T>(mNumber1,mNumber2);
        }
        
        //virtual ~CountIterable() override
        //{
        //    // We own the source iterable passed to us. We destroy it when we
        //    // ourselves are destroyed.
        //    delete mSourceIterable;
        //}
};



template<typename T>
class TakeIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator; // Stores the ``source'' iterator which
                                       // will be used to iterate over the
                                       // elements of the source iterable to
                                       // which accumulate() was applied.
        unsigned mNumber;
        //T mTaken; // Stores the accumulation. This is the last value
                         // returned from next() for this iterator.

        bool mHasIterationStarted; // A flag indicating whether next() was
                                   // called on this iterator. mAccumulation is
                                   // valid only if this flag is true.
        
    public:
        // A newly created ``source'' iterator is passed to this iterator's
        // constructor.
        TakeIterator(IIterator<T> *sourceIterator,unsigned number)
            : mSourceIterator(sourceIterator),
              //mTaken(),
              mNumber(number),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                mHasIterationStarted = true;
                // At first next(), we get the first element from the source
                // iterator and assign it as the accumulation.
                if (mNumber!=0)
                {
                    
                            
                    mNumber=mNumber-1;
                    return mSourceIterator->next();;
                    
                }
            
                else
                {
                    throw StopIteration(); 
                }
            }
            else{
                if (mNumber!=0)
                {
                    
                    //mTaken = mSourceIterator->next();
                    mNumber=mNumber-1;
                    return mSourceIterator->next();;
                    
                }
            
                else
                {
                    throw StopIteration(); 
                }

            }
                

            // The accumulation is returned to represent the next element of
            // this iterator.
            

            // If the source iterator throws a StopIteration exception during
            // the process, it is automatically received by our caller. We do
            // not need to create and throw a new StopIteration exception
            // ourselves. Further next() calls also have the same behavior.
        }
        
        virtual ~TakeIterator() override
        {
            // We own the source iterator passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterator;
        }
};


template<typename T>
class TakeIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable; // Stores the ``source'' iterable to
                                       // which accumulate() was applied to get
                                       // this iterable.
        unsigned mNumber;
    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        TakeIterable(unsigned number1, IIterable<T> *sourceIterable)
            : mSourceIterable(sourceIterable),
            mNumber(number1)
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
            return new TakeIterator<T>(mSourceIterable->iter(),mNumber);
        }
        
        virtual ~TakeIterable() override
        {
            // We own the source iterable passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterable;
        }
};



template<typename T>
class SkipIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator; 
        unsigned mNumber;
        

        bool mHasIterationStarted; 
        
    public:
        
        SkipIterator(IIterator<T> *sourceIterator,unsigned number)
            : mSourceIterator(sourceIterator),
              
              mNumber(number),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                mHasIterationStarted = true;
                while(mNumber!=0)
                {
                    mNumber=mNumber-1;
                    mSourceIterator->next(); 
                }
                //if (mNumber==0)
                //{
                    return mSourceIterator->next();
                //}
            
                //else
                //{
                    //mNumber=mNumber-1;
                    //mSourceIterator->next(); 
                    //return NULL;
                //}
            }
            else
            {
                while(mNumber!=0)
                {
                    mNumber=mNumber-1;
                    mSourceIterator->next(); 
                }
                //if (mNumber==0)
                //{                    
                    
                    return mSourceIterator->next();
                //}
                //else
                //{
                //    //mNumber=mNumber-1;
                //    //mSourceIterator->next();
                //    //return NULL;
                //}
            }
        }
        
        virtual ~SkipIterator() override
        {
            
            delete mSourceIterator;
        }
};


template<typename T>
class SkipIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable; 
        unsigned mNumber;
    public:
        
        SkipIterable(unsigned number1, IIterable<T> *sourceIterable)
            : mSourceIterable(sourceIterable),
            mNumber(number1)
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            
            return new SkipIterator<T>(mSourceIterable->iter(),mNumber);
        }
        
        virtual ~SkipIterable() override
        {
            
            delete mSourceIterable;
        }
};



template<typename T>
class CycleIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator;
        IIterable<T> *mSourceIterable;
        //IIterator<T> *mOriginalSourceIterator;
        //IIterator<T> *original;
        T mReturn;
        bool mHasIterationStarted;
        
    public:

        CycleIterator(IIterator<T> *sourceIterator,IIterable<T> *sourceIterable)
            : mSourceIterator(sourceIterator),
              mSourceIterable(sourceIterable),
              //mOriginalSourceIterator(sourceIterator),
              mReturn(),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                //IIterator<T> *original=new CycleIterator<T>(mOriginalSourceIterator);
                mHasIterationStarted = true;

                try
                {
                    
                    mReturn=mSourceIterator->next();
                    
                }
                
                catch(StopIteration& e)
                {
                    //memcpy(mOriginalSourceIterator,mSourceIterator,sizeof(mOriginalSourceIterator));
                    //IIterator<T> *mSourceIterator{*mOriginalSourceIterator};
                    //*mSourceIterator=(mOriginalSourceIterator);
                    //mSourceIterator=mOriginalSourceIterator;
                    delete mSourceIterator;
                    mSourceIterator = mSourceIterable->iter();
                    return mSourceIterator->next();
                }
                return mReturn;
                
            }
            else{
                
                try
                {
                    
                    mReturn=mSourceIterator->next();
                    
                }
                
                catch(StopIteration& e)
                {
                    //memcpy(mOriginalSourceIterator,mSourceIterator,sizeof(mOriginalSourceIterator));
                    //IIterator<T> *mSourceIterator{*mOriginalSourceIterator};
                    //*mSourceIterator=(mOriginalSourceIterator);
                    //mSourceIterator=mOriginalSourceIterator;
                    delete mSourceIterator;
                    mSourceIterator = mSourceIterable->iter();
                    return mSourceIterator->next();
                }
                return mReturn;
            }
        }
        
        virtual ~CycleIterator() override
        {
            delete mSourceIterator;
        }
};


template<typename T>
class CycleIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable; 
    public:

        CycleIterable(IIterable<T> *sourceIterable)
            : mSourceIterable(sourceIterable)
            
        {
        }
        
        virtual IIterator<T> * iter() const override
        {

            return new CycleIterator<T>(mSourceIterable->iter(),mSourceIterable);
        }
        
        virtual ~CycleIterable() override
        {

            delete mSourceIterable;
        }
};



template<typename T>
class ConcatIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator1;
        IIterator<T> *mSourceIterator2;
        //IIterator<T> *original;
        T mReturn;
        bool mHasIterationStarted;
        
    public:

        ConcatIterator(IIterator<T> *sourceIterator1,IIterator<T> *sourceIterator2)
            : mSourceIterator1(sourceIterator1),
              mSourceIterator2(sourceIterator2),
              mReturn(),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                //IIterator<T> *original=new CycleIterator<T>(mOriginalSourceIterator);
                mHasIterationStarted = true;

                try
                {
                    mReturn=mSourceIterator1->next();                    
                }
                
                catch(StopIteration& e)
                {
                    //memcpy(mOriginalSourceIterator,mSourceIterator,sizeof(mOriginalSourceIterator));
                    //IIterator<T> *mSourceIterator{*mOriginalSourceIterator};
                    //*mSourceIterator=(mOriginalSourceIterator);
                    //mSourceIterator=mOriginalSourceIterator;
                    return mSourceIterator2->next();
                }
                return mReturn;                
            }
            else{
                
                try
                {
                    mReturn=mSourceIterator1->next();                    
                }
                
                catch(StopIteration& e)
                {
                    //memcpy(mOriginalSourceIterator,mSourceIterator,sizeof(mOriginalSourceIterator));
                    //IIterator<T> *mSourceIterator{*mOriginalSourceIterator};

                    //*mSourceIterator=(mOriginalSourceIterator) ;
                    //IIterator<T> *mSourceIterator{original};
                    //mSourceIterator=mOriginalSourceIterator;
                    return mSourceIterator2->next();
                }
                return mReturn;
            }
        }
        
        virtual ~ConcatIterator() override
        {
            delete mSourceIterator1;
            delete mSourceIterator2;
        }
};


template<typename T>
class ConcatIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable1;
        IIterable<T> *mSourceIterable2;

    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        ConcatIterable(IIterable<T> *sourceIterable1,IIterable<T> *sourceIterable2)
            : mSourceIterable1(sourceIterable1),
            mSourceIterable2(sourceIterable2)
            
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
            return new ConcatIterator<T>(mSourceIterable1->iter(),mSourceIterable2->iter());
        }
        
        virtual ~ConcatIterable() override
        {
            // We own the source iterable passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterable1;
            delete mSourceIterable2;
        }
};



template<typename T>
class PairIterator : public IIterator<std::pair<T,T>>
{
    private:
        IIterator<T> *mSourceIterator;
        T mReturn1;
        T mReturn2;
        
        std::pair<T,T> mReturn;
        bool mHasIterationStarted;
        
    public:

        PairIterator(IIterator<T> *sourceIterator1)
            : mSourceIterator(sourceIterator1),
              mReturn1(),
              mReturn2(),
              mReturn(),
              mHasIterationStarted(false)
        {
        }
        
        virtual std::pair<T,T> next() override
        {
            if (!mHasIterationStarted)
            {
                mHasIterationStarted = true;
                try
                {
                    mReturn1=mSourceIterator->next();
                    mReturn2=mSourceIterator->next();                     
                }
                catch(StopIteration& e)
                {

                    throw StopIteration();
                }
                std::pair<T,T> mReturn{mReturn1,mReturn2};   
                return mReturn;   
                //mReturn12=(mReturn1,mReturn2);
                //return mReturn12;          
            }
            else{
                
                try
                {
                    mReturn1=mSourceIterator->next();
                    mReturn2=mSourceIterator->next();                     
                }
                catch(StopIteration& e)
                {

                    throw StopIteration();
                }
                std::pair<T,T> mReturn{mReturn1,mReturn2};   
                return mReturn;
                //mReturn12=(mReturn1,mReturn2);
                //return mReturn12;
            }
        }
        
        virtual ~PairIterator() override
        {
            delete mSourceIterator;

        }
};


template<typename T>
class PairIterable : public IIterable<std::pair<T,T>>
{
    private:
        IIterable<T> *mSourceIterable;


    public:

        PairIterable(IIterable<T> *sourceIterable1)
            : mSourceIterable(sourceIterable1)
        {
        }
        
        virtual IIterator<std::pair<T,T>> * iter() const override
        {

            return new PairIterator<T>(mSourceIterable->iter());
        }
        
        virtual ~PairIterable() override
        {

            delete mSourceIterable;

        }
};


template<typename T>
class MinIterator : public IIterator<T>
{
    private:
        IIterator<T> *mSourceIterator1;
        IIterator<T> *mSourceIterator2;
        //IIterator<T> *original;
        T mSource1;
        T mSource2;
        bool mHasIterationStarted;
        
    public:

        MinIterator(IIterator<T> *sourceIterator1,IIterator<T> *sourceIterator2)
            : mSourceIterator1(sourceIterator1),
              mSourceIterator2(sourceIterator2),
              mSource1(),
              mSource2(),
              mHasIterationStarted(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {
                //IIterator<T> *original=new CycleIterator<T>(mOriginalSourceIterator);
                mHasIterationStarted = true;

                try
                {
                    mSource1=mSourceIterator1->next();
                    mSource2=mSourceIterator2->next();                    
                }
                
                catch(StopIteration& e)
                {
                    throw StopIteration();
                }
                if(mSource1<mSource2)
                {
                    return mSource1;
                }
                else{
                    return mSource2;
                }
                                
            }
            else{
                
                try
                {
                    mSource1=mSourceIterator1->next();
                    mSource2=mSourceIterator2->next();                    
                }
                
                catch(StopIteration& e)
                {
                    throw StopIteration();
                }
                if(mSource1<mSource2)
                {
                    return mSource1;
                }
                else{
                    return mSource2;
                }
            }
        }
        
        virtual ~MinIterator() override
        {
            delete mSourceIterator1;
            delete mSourceIterator2;
        }
};


template<typename T>
class MinIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable1;
        IIterable<T> *mSourceIterable2;

    public:
        // The `source'' iterator, to which accumulate() is applied, is passed
        // to this iterable's constructor.
        MinIterable(IIterable<T> *sourceIterable1,IIterable<T> *sourceIterable2)
            : mSourceIterable1(sourceIterable1),
            mSourceIterable2(sourceIterable2)
            
        {
        }
        
        virtual IIterator<T> * iter() const override
        {
            // Construct a new AccumulateIterator and return it. We create a
            // brand new iterator on the source iterable and pass it to the
            // AccumulateIterator. The AccumulateIterator can use this
            // ``source'' iterator to iterate over the elements of the source
            // iterable.
            return new MinIterator<T>(mSourceIterable1->iter(),mSourceIterable2->iter());
        }
        
        virtual ~MinIterable() override
        {
            // We own the source iterable passed to us. We destroy it when we
            // ourselves are destroyed.
            delete mSourceIterable1;
            delete mSourceIterable2;
        }
};




template<typename T>
class SelectIterator : public IIterator<T>
{
    private:
        IIterable<T> *mSourceIterable;
        IIterator<T> *mSourceIterator1;
        
        IIterator<unsigned> *mSourceIterator2;

        unsigned mIndex;
        T mReturn;
        bool mCheck;
        bool mHasIterationStarted;
        bool mError;
        
    public:

        SelectIterator(IIterable<T> *sourceIterable, IIterator<T> *sourceIterator1,IIterator<unsigned> *sourceIterator2)
            : mSourceIterable(sourceIterable),
              mSourceIterator1(sourceIterator1),
              mSourceIterator2(sourceIterator2),
              
              mIndex(),
              mReturn(),
              mCheck(false),
              mHasIterationStarted(false),
              mError(false)
        {
        }
        
        virtual T next() override
        {
            if (!mHasIterationStarted)
            {

                mHasIterationStarted = true;
                while(!mCheck)
                {
                    try
                    {   
                        mCheck=true;
                        try
                        {
                            mIndex=mSourceIterator2->next();
                        }
                        catch(StopIteration& e)
                        {   
                            mError=true;
                            throw StopIteration();
                        }
                        
                        
                        while (mIndex!=0)
                        {
                            mIndex=mIndex-1;
                            mSourceIterator1->next();
                        }
                        mReturn=mSourceIterator1->next();                    
                    }

                    catch(StopIteration& e)
                    {
                        if(mError==true)
                        {
                            throw StopIteration();
                        }
                        mCheck=false;
                        //return mSourceIterator2->next();
                    }
                    
                }
                mCheck=false;
                delete mSourceIterator1;
                mSourceIterator1=mSourceIterable->iter();
                mHasIterationStarted=false;
                return mReturn;                
            }
            else{
                
                while(!mCheck)
                {
                    try
                    {   
                        mCheck=true;
                        try
                        {
                            mIndex=mSourceIterator2->next();
                        }
                        catch(StopIteration& e)
                        {   
                            mError=true;
                            throw StopIteration();
                        }
                        
                        
                        while (mIndex!=0)
                        {
                            mIndex=mIndex-1;
                            mSourceIterator1->next();
                        }
                        mReturn=mSourceIterator1->next();                    
                    }

                    catch(StopIteration& e)
                    {
                        if(mError==true)
                        {
                            throw StopIteration();
                        }
                        mCheck=false;
                        //return mSourceIterator2->next();
                    }
                    
                }
                mCheck=false;
                delete mSourceIterator1;
                mSourceIterator1=mSourceIterable->iter();
                mHasIterationStarted=false;
                return mReturn;
            }
        }
        
        virtual ~SelectIterator() override
        {
            delete mSourceIterator1;
            delete mSourceIterator2;
            //delete mSourceIterable;
        }
};


template<typename T>
class SelectIterable : public IIterable<T>
{
    private:
        IIterable<T> *mSourceIterable1;
        IIterable<unsigned> *mSourceIterable2;

    public:

        SelectIterable(IIterable<T> *sourceIterable1,IIterable<unsigned> *sourceIterable2)
            : mSourceIterable1(sourceIterable1),
            mSourceIterable2(sourceIterable2)
            
        {
        }
        
        virtual IIterator<T> * iter() const override
        {

            return new SelectIterator<T>(mSourceIterable1,mSourceIterable1->iter(),mSourceIterable2->iter());
        }
        
        virtual ~SelectIterable() override
        {

            delete mSourceIterable1;
            delete mSourceIterable2;
        }
};


template<typename T>
IIterable<T> * repeat(T v){
        return new RepeatIterable<T>(v);
}


template<typename T>
IIterable<T> * count(T input1,T input2)
{
    return new CountIterable<T>(input1,input2);
}

template<typename T>
IIterable<T> * take(unsigned number,IIterable<T> *i)
{
    return new TakeIterable<T>(number,i);
}

template<typename T>
IIterable<T> * skip(unsigned k , IIterable <T > * i )
{
    return new SkipIterable<T>(k,i);
}

template<typename T>
IIterable<T> * cycle(IIterable <T > * i )
{
    return new CycleIterable<T>(i);
}

template<typename T>
IIterable<T> * concat( IIterable <T > * i, IIterable <T > * j  )
{
    return new ConcatIterable<T>(i,j);
}
//sıkıntı var... std::pair kısmında
template < typename T >
IIterable<std::pair<T, T>> * pair(IIterable<T> *i)
{
    return new PairIterable<T>(i);
}


template<typename T>
IIterable<T> * min( IIterable <T > * i, IIterable <T > * j  )
{
    return new MinIterable<T>(i,j);
}

template<typename T>
IIterable<T> * select( IIterable <T > * i, IIterable <unsigned > * s  )
{
    return new SelectIterable<T>(i,s);
}
