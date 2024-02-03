package ceng.ceng351.cengfactorydb;
import java.sql.*;
public class CENGFACTORYDB implements ICENGFACTORYDB{
    /**
     * Place your initialization code inside if required.
     *
     * <p>
     * This function will be called before all other operations. If your implementation
     * need initialization , necessary operations should be done inside this function. For
     * example, you can set your connection to the database server inside this function.
     */
    private static String user = "e2575983"; // Your userName
    private static String password = "&mCr3gr(gnB7"; // Your password
    private static String host = "144.122.71.128"; // host name
    private static String database = "db2575983"; // Your database name
    private static int port = 8080; // port

    private static Connection connection = null;



    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database + "?useSSL=false";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        int ret=dropTables();
    }

    /**
     * Should create the necessary tables when called.
     *
     * @return the number of tables that are created successfully.
     */

    public int createTables() {

        String[] stringler = {
                "CREATE TABLE IF NOT EXISTS`Factory`(`factoryId` INT NOT NULL,`factoryName` TEXT,`factoryType` TEXT,`country` TEXT, PRIMARY KEY(`factoryId`));",
                "CREATE TABLE IF NOT EXISTS`Employee`(`employeeId` INT NOT NULL,`employeeName` TEXT , `department` TEXT, `salary` INT,	PRIMARY KEY(`employeeId`) );",
                "CREATE TABLE IF NOT EXISTS`Works_In`(`factoryId` INT NOT NULL,`employeeId` INT NOT NULL,`startDate` DATE ,Foreign KEY(`employeeId`) References `Employee`(`employeeId`) ON DELETE CASCADE, Foreign Key(`factoryId`) References `Factory`(`factoryId`) ON DELETE CASCADE, PRIMARY KEY(`employeeId`,`factoryId`) );",
                "CREATE TABLE IF NOT EXISTS`Product`(`productId` INT NOT NULL,`productName` TEXT , `productType` TEXT , PRIMARY KEY(`productID`));",
                "CREATE TABLE IF NOT EXISTS`Produce`(`factoryId` INT NOT NULL,`productId` INT NOT NULL,`amount` INT , `productionCost` INT, Foreign Key(`productId`) References `Product`(`productId`) ON DELETE CASCADE, Foreign Key(`factoryId`) References `Factory`(`factoryId`) ON DELETE CASCADE,	PRIMARY KEY(`factoryId`,`productId`));",
                "CREATE TABLE IF NOT EXISTS`Shipment`(`factoryId` INT NOT NULL, `productId` INT NOT NULL,`amount` INT ,`pricePerUnit` INT,Foreign Key(`productId`) References `Product`(`productId`)ON DELETE CASCADE, Foreign Key(`factoryId`) References `Factory`(`factoryId`)ON DELETE CASCADE,PRIMARY KEY(`factoryId`,`productId`));"
        };
        int res=0;
        for (String s : stringler) {
            try {
                Statement statement = connection.createStatement();
                statement.executeUpdate(s);
                res++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return res;
    }
    public int dropTables() {
        int res = 0;
        String[] tableNames = { "Produce", "Shipment" , "Product", "Works_In", "Employee", "Factory"};
        String queryDropTable = "DROP TABLE IF EXISTS `";

        for (String s : tableNames) {
            try {
                Statement statement = connection.createStatement();
                statement.executeUpdate(queryDropTable + s + "`;");
                res++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return res;

    }

    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories) {
        int res=0;
        for(Factory f:factories){
            try {
                int fid=f.getFactoryId();
                String country=f.getCountry();
                String type=f.getFactoryType();
                String name=f.getFactoryName();

                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Factory`VALUES(?,?,?,?) ;");
                pstatement.setInt(1,fid);
                pstatement.setString(2,name);
                pstatement.setString(3,type);
                pstatement.setString(4,country);
                pstatement.executeUpdate();
                res++;
            }
            catch (SQLException e){
                e.printStackTrace();
            }
        }



        return res;

    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees) {
        int res=0;
        for(Employee emp:employees) {
            try {
                int eid = emp.getEmployeeId();
                String name = emp.getEmployeeName();
                int salary = emp.getSalary();
                String department = emp.getDepartment();

                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Employee`VALUES(?,?,?,?) ;");
                pstatement.setInt(1, eid);
                pstatement.setString(2, name);
                pstatement.setString(3, department);
                pstatement.setInt(4, salary);
                pstatement.executeUpdate();
                res++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return res;
    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns) {
        int res=0;
        for(WorksIn wi:worksIns) {
            try {
                int eid = wi.getEmployeeId();
                int factoryId = wi.getFactoryId();
                String startDate = wi.getStartDate();


                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Works_In`VALUES(?,?,?) ;");
                pstatement.setInt(1, factoryId);
                pstatement.setInt(2, eid);
                pstatement.setString(3, startDate);
                pstatement.executeUpdate();
                res++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return res;
    }

    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products) {
        int res=0;
        for(Product pro:products) {
            try {
                int pid = pro.getProductId();
                String name = pro.getProductName();
                String protype = pro.getProductType();

                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Product`VALUES(?,?,?) ;");
                pstatement.setInt(1, pid);
                pstatement.setString(2, name);
                pstatement.setString(3, protype);
                pstatement.executeUpdate();
                res++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return res;
    }


    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces) {
        int res=0;
        for(Produce pro:produces) {
            try {
                int pid = pro.getProductId();
                int fid = pro.getFactoryId();
                int cost = pro.getProductionCost();
                int amount = pro.getAmount();

                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Produce` VALUES(?,?,?,?);");
                pstatement.setInt(1, fid);
                pstatement.setInt(2, pid);
                pstatement.setInt(3, amount);
                pstatement.setInt(4, cost);
                pstatement.executeUpdate();
                res++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return res;
    }


    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments) {
        int res=0;
        for(Shipment shp:shipments) {
            try {
                int pid = shp.getProductId();
                int fid = shp.getFactoryId();
                int price = shp.getPricePerUnit();
                int amount = shp.getAmount();

                PreparedStatement pstatement = this.connection.prepareStatement("INSERT INTO `Shipment` VALUES(?,?,?,?);");
                pstatement.setInt(1, fid);
                pstatement.setInt(2, pid);
                pstatement.setInt(3, amount);
                pstatement.setInt(4, price);
                pstatement.executeUpdate();
                res++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return res;
    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country)
    {
        try{
            PreparedStatement pstatementNUM = this.connection.prepareStatement("Select COUNT(*) From `Factory` F Where F.Country=?;");
            pstatementNUM.setString(1, country);
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            Factory[] result=new Factory[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement("Select * From `Factory` F Where F.Country=? Order By F.`factoryId` ASC;");
            pstatement.setString(1, country);


            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new Factory(rs.getInt(1),rs.getString(2),rs.getString(3),rs.getString(4));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new Factory[0];
    }



    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee()
    {
        try{
            PreparedStatement pstatementNUM = this.connection.prepareStatement("Select COUNT(*) From Factory F1,(Select F.factoryId From Factory F Except Select F.factoryId From Works_In W, Factory F Where W.factoryId=F.factoryId) AS A Where F1.factoryId=A.factoryID;");
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            Factory[] result=new Factory[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement("Select F1.factoryId, F1.factoryName, F1.factoryType, F1.country From Factory F1,(Select F.factoryId From Factory F Except Select F.factoryId From Works_In W, Factory F Where W.factoryId=F.factoryId) AS A Where F1.factoryId=A.factoryID Order By F1.factoryId ASC;");

            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new Factory(rs.getInt(1),rs.getString(2),rs.getString(3),rs.getString(4));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new Factory[0];
    }

    /**
     * Should return all factories that produce all products for a particular productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType)
    {
        try{
            PreparedStatement pstatementNUM = this.connection.prepareStatement("Select COUNT(*) From Factory F Where NOT EXISTS (Select P.productId From Product P Where P.productType=? Except Select P1.productId From Produce P1 Where P1.factoryId=F.factoryId) Order By F.factoryId ASC;");
            pstatementNUM.setString(1, productType);
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            Factory[] result=new Factory[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement("Select F.factoryId, F.factoryName, F.factoryType, F.country From Factory F Where NOT EXISTS (Select P.productId From Product P Where P.productType=? Except Select P1.productId From Produce P1 Where P1.factoryId=F.factoryId) Order By F.factoryId ASC;");
            pstatement.setString(1, productType);
            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new Factory(rs.getInt(1),rs.getString(2),rs.getString(3),rs.getString(4));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new Factory[0];
    }


    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped()
    {
        try{
            PreparedStatement pstatementNUM = this.connection.prepareStatement("Select COUNT(DISTINCT P1.productId) From Produce P, Product P1 Where  P.productId=P1.productId and NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)");
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            Product[] result=new Product[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement("Select DISTINCT P1.productId, P1.productName, P1.productType From Produce P, Product P1 Where  P.productId=P1.productId and NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId) Order By P.productId");
            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new Product(rs.getInt(1),rs.getString(2),rs.getString(3));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new Product[0];
    }


    /**
     * For a given factoryId and department, should return the average salary of
     *     the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department)
    {
        try{
            PreparedStatement pstatement = this.connection.prepareStatement("Select AVG(E.salary) From Works_In W, Employee E Where W.employeeId=E.employeeId and W.factoryId=? and E.department=? Group By W.factoryId;");
            pstatement.setInt(1, factoryId);
            pstatement.setString(2, department);
            ResultSet rs=pstatement.executeQuery();
            rs.next();
            return  (rs.getDouble(1));
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return 0.0;
    }


    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts()
    {
        try{
            String qnum="Select COUNT(*) " +
                    "From Product Pr, " +

                    "(Select P.factoryId as factoryId,P.productId as productId,0-(P.amount * P.productionCost) as profit "+
                    "From Produce P "+
                    "Where (P.productId,P.factoryId) IN "+
                    "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                    "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp "+

                    "Where Pr.productId = Temp.productId and Temp.profit = " +
                    "(Select Max(Temp1.profit) From " +
                    "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                    "From Produce P "+
                    "Where (P.productId,P.factoryId) IN "+
                    "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                    "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp1 "+
                    "Where Temp.factoryId = Temp1.factoryId) " ;
            PreparedStatement pstatementNUM = this.connection.prepareStatement(qnum);
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            String query=
                    "Select Temp.factoryId, Pr.productId, Pr.productName, Pr.productType, Temp.profit " +
                            "From Product Pr, " +

                            "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                            "From Produce P "+
                            "Where (P.productId,P.factoryId) IN "+
                            "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
            "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp "+

                            "Where Pr.productId = Temp.productId and Temp.profit = " +
                            "(Select Max(Temp1.profit) From " +
                            "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                            "From Produce P "+
                            "Where (P.productId,P.factoryId) IN "+
                            "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                            "UNION "+
                            "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                            "From Produce P, Shipment S " +
                            "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp1 "+
                            "Where Temp.factoryId = Temp1.factoryId) " +
                    "Order By Temp.profit desc,Temp.factoryId asc;";




            QueryResult.MostValueableProduct[] result=new QueryResult.MostValueableProduct[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement(query);
            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new QueryResult.MostValueableProduct(rs.getInt(1),rs.getInt(2),rs.getString(3),rs.getString(4),rs.getDouble(5));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new QueryResult.MostValueableProduct[0];
    }

    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory()
    {
        try{
            String queryNum= "SELECT COUNT(*) " +
                    "From Product Pr, " +
                    "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                    "From Produce P "+
                    "Where (P.productId,P.factoryId) IN "+
                    "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                    "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp "+
                    "Where Pr.productId=Temp.productId and Temp.profit= (Select Max(Temp1.profit) " +
                    "From " +
                    "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                    "From Produce P "+
                    "Where (P.productId,P.factoryId) IN "+
                    "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                    "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp1 "+
                    "Where Temp.productId=Temp1.productId) ";
            PreparedStatement pstatementNUM = this.connection.prepareStatement(queryNum);
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            QueryResult.MostValueableProduct[] result=new QueryResult.MostValueableProduct[column_sayısı];
            String query= "Select Temp.factoryId, Pr.productId, Pr.productName, Pr.productType, Temp.profit " +
                            "From Product Pr, " +
                    "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                    "From Produce P "+
                    "Where (P.productId,P.factoryId) IN "+
                    "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                    "UNION "+
                    "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                    "From Produce P, Shipment S " +
                    "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp "+
                            "Where Pr.productId=Temp.productId and Temp.profit= (Select Max(Temp1.profit) " +
                                                                                "From " +
                                                                                        "(Select P.factoryId as factoryId,P.productId as productId,(-1)*(P.amount * P.productionCost) as profit "+
                                                                                        "From Produce P "+
                                                                                        "Where (P.productId,P.factoryId) IN "+
                                                                                        "(Select P.productId, P.factoryId From Produce P Where  NOT EXISTS	(SELECT * From Shipment S Where S.factoryId=P.factoryId and S.productId=P.productId)) "+
                                                                                        "UNION "+
                                                                                        "(Select S.factoryId as factoryId,S.productId as productId,((S.amount * S.pricePerUnit) -(P.amount * P.productionCost)) as profit " +
                                                                                        "From Produce P, Shipment S " +
                                                                                        "Where P.productId = S.productId and P.factoryId = S.factoryId )) AS Temp1 "+
                                                                                "Where Temp.productId=Temp1.productId) " +
                            "Order By Temp.profit desc, Pr.productId asc;";
            PreparedStatement pstatement = this.connection.prepareStatement(query);
            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new QueryResult.MostValueableProduct(rs.getInt(1),rs.getInt(2),rs.getString(3),rs.getString(4),rs.getDouble(5));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new QueryResult.MostValueableProduct[0];
    }


    /**
     * For each department, should return all employees that are paid under the
     *     average salary for that department. You consider the employees
     *     that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments()
    {
        try{
            String queryNum="Select COUNT(*) " +
                    "From " +
                    "(" +
                    "(Select E1.employeeId as empid, E1.employeeName as name, E1.department as dept, CASE WHEN E1.salary IS NULL THEN 0 " +
                    "ELSE E1.salary " +
                    "END AS salary  From Employee E1, Works_In W " +
                    "Where W.employeeId=E1.employeeId) "+
                    "UNION "+
                    "(Select E2.employeeId as empid, E2.EmployeeName as name,E2.department as dept, 0 as salary From Employee E2 " +
                    "Where E2.employeeId "+
                    "IN (" +
                    "(Select DISTINCT E3.EmployeeId From Employee E3) " +
                    "EXCEPT " +
                    "(Select DISTINCT E1.employeeId From Employee E1, Works_In W Where E1.employeeId=W.employeeId ) " +
                    ") " +
                    ") " +
                    ") AS Emp "+
                    "Where Emp.salary < " +
                    "(	Select AVG(AYTAC.salary) From " +
                    "((Select E1.employeeId as empid, E1.employeeName as name, E1.department as dept, E1.salary as salary  From Employee E1, Works_In W " +
                    "Where W.employeeId=E1.employeeId)"+
                    "UNION "+
                    "(Select E2.employeeId as empid, E2.EmployeeName as name,E2.department as dept, 0 as salary From Employee E2 " +
                    "Where E2.employeeId "+
                    "IN ((Select DISTINCT E3.EmployeeId From Employee E3) " +
                    "EXCEPT " +
                    "(Select DISTINCT E1.employeeId From Employee E1, Works_In W Where E1.employeeId=W.employeeId )))) AS AYTAC "+

                    "Where AYTAC.dept=Emp.dept) ";
            PreparedStatement pstatementNUM = this.connection.prepareStatement(queryNum);
            ResultSet rsnum=pstatementNUM.executeQuery();
            rsnum.next();
            int column_sayısı=rsnum.getInt(1);

            String query=
                    "Select Emp.empid employeeId, Emp.name employeeName, Emp.dept department, Emp.salary " +
                    "From " +
                    "(" +
                            "(Select E1.employeeId as empid, E1.employeeName as name, E1.department as dept, CASE WHEN E1.salary IS NULL THEN 0 " +
                            "ELSE E1.salary " +
                            "END AS salary  From Employee E1, Works_In W " +
                    "Where W.employeeId=E1.employeeId) "+
                    "UNION "+
                    "(Select E2.employeeId as empid, E2.EmployeeName as name,E2.department as dept, 0 as salary From Employee E2 " +
                    "Where E2.employeeId "+
                    "IN (" +
                            "(Select DISTINCT E3.EmployeeId From Employee E3) " +
                            "EXCEPT " +
                            "(Select DISTINCT E1.employeeId From Employee E1, Works_In W Where E1.employeeId=W.employeeId ) " +
                       ") " +
                    ") " +
                            ") AS Emp "+
                    "Where Emp.salary < " +
                    "(	Select AVG(AYTAC.salary) From " +
                    "((Select E1.employeeId as empid, E1.employeeName as name, E1.department as dept, E1.salary as salary  From Employee E1, Works_In W " +
                    "Where W.employeeId=E1.employeeId)"+
                    "UNION "+
                    "(Select E2.employeeId as empid, E2.EmployeeName as name,E2.department as dept, 0 as salary From Employee E2 " +
                    "Where E2.employeeId "+
                    "IN ((Select DISTINCT E3.EmployeeId From Employee E3) " +
                    "EXCEPT " +
                    "(Select DISTINCT E1.employeeId From Employee E1, Works_In W Where E1.employeeId=W.employeeId )))) AS AYTAC "+

                    "Where AYTAC.dept=Emp.dept) " +
                    "Order By Emp.empid ASC;";

            QueryResult.LowSalaryEmployees[] result=new QueryResult.LowSalaryEmployees[column_sayısı];
            PreparedStatement pstatement = this.connection.prepareStatement(query);
            ResultSet rs=pstatement.executeQuery();
            int i=0;
            while(rs.next()){
                result[i]=new QueryResult.LowSalaryEmployees(rs.getInt(1),rs.getString(2),rs.getString(3),rs.getInt(4));
                i++;
            }
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return new QueryResult.LowSalaryEmployees[0];
    }


    /**
     * For the products of given productType, increase the productionCost of every unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage)
    {
        String query=
        "Update Produce P Set P.productionCost=(P.productionCost*(1.0+?)) Where P.productId IN(Select Pr.productId From Product Pr Where Pr.productType= ?);";
        try{
            PreparedStatement pstatement = this.connection.prepareStatement(query);
            pstatement.setDouble(1, percentage);
            pstatement.setString(2, productType);
            int result=pstatement.executeUpdate();
            return  result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return 0;
    }


    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate)
    {
        try{
            PreparedStatement pstatement = this.connection.prepareStatement("DELETE FROM Employee WHERE employeeId IN ((Select DISTINCT E.EmployeeId From Employee E) EXCEPT (Select DISTINCT employeeId From Works_In W Where W.startDate>=?));");
            pstatement.setString(1, givenDate);
            int result=pstatement.executeUpdate();
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return 0;
    }


    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     *  THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     *  YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     *  IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     */

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Peers are considered tied and receive the same rank. After
     * that, there should be a gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Everything is the same but after ties, there should be no
     * gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank2() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each factory, calculate the most profitable 4th product.
     *
     * @return QueryResult.FactoryProfit
     */
    public QueryResult.FactoryProfit calculateFourth() {
        return new QueryResult.FactoryProfit(0,0,0);
    }

    /**
     * Determine the salary variance between an employee and another
     * one who began working immediately after the first employee (by
     * startDate), for all employees.
     *
     * @return QueryResult.SalaryVariant[]
     */
    public QueryResult.SalaryVariant[] calculateVariance() {
        return new QueryResult.SalaryVariant[0];
    }

    /**
     * Create a method that is called once and whenever a Product starts
     * losing money, deletes it from Produce table
     *
     * @return void
     */
    public void deleteLosing() {

    }
}
