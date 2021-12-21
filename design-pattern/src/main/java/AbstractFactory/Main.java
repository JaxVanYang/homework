package AbstractFactory;

public class Main {
    public static void main(String[] args) {
        User user = new User();
        user.id = 1;
        user.name = "Steve";

        DatabaseFactory mysqlFactory = new MysqlFactory();
        DatabaseFactory oracleFactory = new OracleFactory();

        UserService mysqlService = mysqlFactory.createUserService();
        mysqlService.insert(user);
        mysqlService.getUser(1);

        UserService oracleService = oracleFactory.createUserService();
        oracleService.insert(user);
        oracleService.getUser(1);
    }
}
