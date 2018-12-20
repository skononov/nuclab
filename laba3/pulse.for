	FUNCTION TEST(X)
        IF(X.GT.0) THEN
          TEST=(EXP(-X/2)-EXP(-X))/(1-1/2)
	ELSE
          TEST=0
	ENDIF
        END