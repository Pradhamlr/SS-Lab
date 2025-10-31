SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE print_square(n NUMBER)
IS
    sq NUMBER;
BEGIN
    sq := n * n;
    DBMS_OUTPUT.PUT_LINE('Square of ' || n || ' is ' || sq);
END;
/


BEGIN
    print_square(&n);
END;
/
