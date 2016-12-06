#include <QStringList>
#include "utils.h"
#include "cliquenetworkmanager.h"

const int clusters = 8;
const int fanals = 256;

int main()
{
    QStringList automata = {
        "A -> a -> B",
        "A -> b -> D",
        "B -> a -> C",
        "B -> b -> G",
        "C -> c -> A",
        "D -> a -> C",
        "D -> b -> E",
        "E -> b -> D",
        "E -> a -> F",
        "F -> a -> C",
        "G -> c -> C",
        "G -> a -> F",
    };

    CliqueNetwork States;
    States.init(clusters,fanals);
    CliqueNetwork StateFlurry;
    StateFlurry.init(clusters, fanals);
    CliqueNetwork Transitions;
    Transitions.init(clusters, fanals);
    CliqueNetworkManager mgr;
    mgr.addNetwork(States);
    mgr.addNetwork(StateFlurry);
    mgr.addNetwork(Transitions);

    QHash<QString, Clique> transitions;
    QHash<QString, Clique> states;

    for (QString s : automata) {
        auto abc = s.split(" -> ");
        QString state = abc[0];
        QString transition = abc[1];
        QString target = abc[2];

        if (!transitions.contains(transition)) {
            transitions.insert(transition, randomClique(clusters,fanals));
            Transitions.addClique(transitions[transition]);
        }
        if (!states.contains(state)) {
            states.insert(state, randomClique(clusters,fanals));
            States.addClique(states[state]);
        }
        if (!states.contains(target)) {
            states.insert(target, randomClique(clusters,fanals));
            States.addClique(states[target]);
        }

        Clique targetCl = randomClique(clusters, fanals);
        StateFlurry.addClique(targetCl);

        StateFlurry.addLink(targetCl, &States, states[target]);
        States.addLink(states[state], &StateFlurry, targetCl);
        Transitions.addLink(transitions[transition], &StateFlurry, targetCl);
    }

    return 0;
}

