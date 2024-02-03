import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
    private ArrayList<Integer> keys;
    private ArrayList<CengTreeNode> children;

    public CengTreeNodeInternal(CengTreeNode parent)
    {
        super(parent);
        keys = new ArrayList<Integer>();
        children = new ArrayList<CengTreeNode>();
        this.type = CengNodeType.Internal;
    }

    // GUI Methods - Do not modify
    public ArrayList<CengTreeNode> getAllChildren()
    {
        return this.children;
    }
    public Integer keyCount()
    {
        return this.keys.size();
    }
    public Integer keyAtIndex(Integer index)
    {
        if(index >= this.keyCount() || index < 0)
        {
            return -1;
        }
        else
        {
            return this.keys.get(index);
        }
    }

    // Extra Functions
    public Integer findPosition(Integer key){
        int book_count=this.keys.size();
        int deneme=0;
        for(int i=0;i<book_count;i++)
        {
            if(this.keys.get(i)<=key)
            {
                deneme++;
                continue;
            }
            break;
        }
        return deneme;

    }

    public Integer findIndexofChild(CengTreeNode src)
    {
        return this.children.indexOf(src);
    }

    public CengTreeNode findPath(Integer key)
    {
        return this.children.get(findPosition(key));
    }
    public CengTreeNodeInternal pushup(){
        Integer orta_konum =  this.keyCount()/2;
        Integer ortadaki_key = this.keyAtIndex(orta_konum);
        CengTreeNodeInternal parent_node = (CengTreeNodeInternal) this.getParent();


        CengTreeNode ara;
        Integer tmp_key;

        CengTreeNodeInternal left_node = new CengTreeNodeInternal(parent_node);

        for(int i = 0; i < orta_konum; i++) {
            ara = this.getChild(i);
            ara.setParent(left_node);
            left_node.cocukEkle(i, ara);

            tmp_key = this.keyAtIndex(i);
            left_node.insertKey(i, tmp_key);
        }

        CengTreeNodeInternal right_node = new CengTreeNodeInternal(parent_node);

        for(int i = orta_konum + 1; i < this.keyCount(); i++) {
            ara = this.getChild(i);
            ara.setParent(right_node);
            right_node.cocukEkle(i - orta_konum - 1, ara);

            tmp_key = this.keyAtIndex(i);
            right_node.insertKey(i - orta_konum - 1, tmp_key);
        }

        ara = this.getChild(orta_konum);
        ara.setParent(left_node);
        left_node.cocukEkle(orta_konum, ara);

        ara = this.getChild(this.keyCount());
        ara.setParent(right_node);
        right_node.cocukEkle(this.keyCount() - orta_konum -1, ara);

        if(parent_node == null)
        {
            //Eger parent bos ise yukarıya yeni bir porent oluşturulur ve o doldurulur
            parent_node = new CengTreeNodeInternal(null);
            left_node.setParent(parent_node);
            right_node.setParent(parent_node);

            parent_node.insertKey(0, ortadaki_key);
            parent_node.cocukEkle(0, left_node);
            parent_node.cocukEkle(1, right_node);
        }
        else
        {
            //eger parent bos degilse parentın ilgili yerine pushup yapılır
            Integer key_position = parent_node.findIndexofChild(this);
            parent_node.insertKey(key_position, ortadaki_key);
            parent_node.updateChild(key_position, left_node);
            parent_node.cocukEkle(key_position + 1, right_node);
        }
        return parent_node;
    }
    public CengTreeNode getChild(Integer position)
    {
        return this.children.get(position);
    }

    public void insertKey(Integer position, Integer key)
    {
        this.keys.add(position, key);
    }

    public void cocukEkle(Integer position, CengTreeNode child)
    {
        this.children.add(position, child);
    }

    public void updateChild(Integer position, CengTreeNode child)
    {
        this.children.set(position, child);
    }
}
