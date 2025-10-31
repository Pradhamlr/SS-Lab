SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION find_square(n NUMBER)
RETURN NUMBER
IS
    sq NUMBER;
BEGIN
    sq := n * n;
    RETURN sq;
END;
/

DECLARE
    num NUMBER := &n;
    result NUMBER;
BEGIN
    result := find_square(num);
    DBMS_OUTPUT.PUT_LINE('Square of ' || num || ' is ' || result);
END;
/


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
