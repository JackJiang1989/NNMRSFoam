// Residual control used
if (residualControlUsed)
{
    bool UConv = false;
    bool pConv = false;
    bool TConv = false;

    // Check which field is not used for control
    {
        if (UTol == -1 || !momentumPredictor)
        {
            UConv =  true;
        }

        if (pTol == -1)
        {
            pConv = true;
        }

        if (TTol == -1)
        {
            TConv = true;
        }
    }

    // Get the last initial residual of the solvers
    if (momentumPredictor && !UConv)
    {
        if (UTol > cmptMax(solvPerfU.initialResidual()))
        {
            UConv = true;
        }
    }

    if (!pConv)
    {
        if (pTol > solvPerfp_rgh.initialResidual())
        {
            pConv = true;
        }
    }

    if (!TConv)
    {
        if (TTol > solvPerfE.initialResidual())
        {
            TConv = true;
        }
    }

    // Check if each field is converged
    if (UConv && pConv && TConv)
    {
        resReachedFluid = true;
    }
}
