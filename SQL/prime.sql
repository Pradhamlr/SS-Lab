SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION is_prime(n NUMBER)
RETURN VARCHAR2
IS
    i NUMBER;
    flag BOOLEAN := TRUE;
BEGIN
    IF n <= 1 THEN
        RETURN n || ' is NOT a prime number.';
    END IF;

    FOR i IN 2..FLOOR(SQRT(n)) LOOP
        IF MOD(n, i) = 0 THEN
            flag := FALSE;
            EXIT;
        END IF;
    END LOOP;

    IF flag THEN
        RETURN n || ' is a PRIME number.';
    ELSE
        RETURN n || ' is NOT a PRIME number.';
    END IF;
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(is_prime(&n));
END;
/




SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE check_prime(n NUMBER)
IS
    i NUMBER;
    flag BOOLEAN := TRUE;
BEGIN
    IF n <= 1 THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is NOT a prime number.');
        RETURN;
    END IF;

    FOR i IN 2..FLOOR(SQRT(n)) LOOP
        IF MOD(n, i) = 0 THEN
            flag := FALSE;
            EXIT;
        END IF;
    END LOOP;

    IF flag THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is a PRIME number.');
    ELSE
        DBMS_OUTPUT.PUT_LINE(n || ' is NOT a PRIME number.');
    END IF;
END;
/

BEGIN
    check_prime(&n);
END;
/
