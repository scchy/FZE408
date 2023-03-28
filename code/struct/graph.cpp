


template <class TypOfVer, class TypeOfEdge>
class graph {
    public:
        virtual void insert(TypeOfVer x, TypeOfVer y, TypOfEdge w) = 0;
        virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
        virtual ~graph();
        int numOfVer() const {return Vers;}
        int numOfEdge() const {return Edges;}
    
    protected:
        int Vers, Edges;
}


