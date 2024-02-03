import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
    private ArrayList<CengBook> books;
    // TODO: Any extra attributes

    public CengTreeNodeLeaf(CengTreeNode parent)
    {
        super(parent);

        books = new ArrayList<CengBook>();
        this.type = CengNodeType.Leaf;
    }

    public int bookCount()
    {
        return books.size();
    }
    public Integer bookKeyAtIndex(Integer index)
    {
        if(index >= this.bookCount()) {
            return -1;
        } else {
            CengBook book = this.books.get(index);

            return book.getBookID();
        }
    }

    // Extra Functions
    public void addBook(CengBook book){

        Integer book_id = book.getBookID();
        int book_count=this.books.size();
        int deneme=0;
        for(int i=0;i<book_count;i++)
        {
            if(this.books.get(i).getBookID()<book_id)
            {
                deneme++;
                continue;
            }
            break;
        }
        this.books.add(deneme, book);
    }

    public Integer findBook(Integer bookId){

        int book_count=this.books.size();
        int i;
        for( i=book_count-1;i>-1;i--)
        {
            if(!bookId.equals(this.books.get(i).getBookID()))
            {
                continue;
            }
            break;
        }
        return i;
    }

    public CengBook getBook(Integer position){
        return this.books.get(position);
    }
    public void insertBook(Integer position, CengBook book)
    {
        this.books.add(position, book) ;
    }

    public CengTreeNodeInternal copyup()
    {
        int mid_position =  this.bookCount()/2;
        Integer mid_key = this.bookKeyAtIndex(mid_position);
        CengTreeNodeInternal parent_node = (CengTreeNodeInternal) this.getParent();

        CengTreeNodeLeaf left_node = new CengTreeNodeLeaf(parent_node);

        for(int i = 0; i < mid_position; i++) {
            left_node.insertBook(i, this.getBook(i));
        }

        CengTreeNodeLeaf right_node = new CengTreeNodeLeaf(parent_node);

        for(int i = mid_position; i < this.bookCount(); i++) {
            right_node.insertBook(i - mid_position, this.getBook(i));
        }

        //eger parent boş ise level sayısı artacak
        if(parent_node == null){
            parent_node = new CengTreeNodeInternal(null);
            left_node.setParent(parent_node);
            right_node.setParent(parent_node);

            parent_node.insertKey(0, mid_key);
            parent_node.cocukEkle(0, left_node);
            parent_node.cocukEkle(1, right_node);
        }
        //eger boş değilse parentte boş olan yere pushlayacaz
        else
        {
            Integer key_position = parent_node.findIndexofChild(this);
            parent_node.insertKey(key_position, mid_key);
            parent_node.updateChild(key_position, left_node);
            parent_node.cocukEkle(key_position + 1, right_node);
        }

        return parent_node;
    }
}
