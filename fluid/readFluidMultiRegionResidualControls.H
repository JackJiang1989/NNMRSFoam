    const dictionary& residualControl =
        mesh.solutionDict().subDict("SIMPLE").subOrEmptyDict("residualControl");

    scalar UTol = -1.;
    scalar TTol = -1.;
    scalar pTol = -1.;

    if (!residualControl.empty())
    {
        if (!residualControl.subOrEmptyDict("U").empty())
        {
            UTol = readScalar(residualControl.subDict("U").lookup("tolerance"));
        }

        if (!residualControl.subOrEmptyDict("p").empty())
        {
            pTol =
                readScalar
                (
                    residualControl.subDict("p").lookup("tolerance")
                );
        }

        if (!residualControl.subOrEmptyDict("T").empty())
        {
            TTol = readScalar(residualControl.subDict("T").lookup("tolerance"));
        }

        //- Residual control used?
        if (UTol != -1 || TTol != -1 || pTol != -1)
        {
            residualControlUsed = true;
            resReachedFluid = false;
        }
    }
