#ifdef CONFIG_NODES_SHIFT
#define NODES_SHIFT     CONFIG_NODES_SHIFT
#else
#define NODES_SHIFT     0
#endif

#define MAX_NUMNODES    (1 << NODES_SHIFT)

#if MAX_NUMNODES > 1
static inline int node_state(int node, enum node_states state)
{
  return node_isset(node, node_states[state]);
}
#else
static inline int node_state(int node, enum node_states state)
{
  return node == 0;
}
#endif
