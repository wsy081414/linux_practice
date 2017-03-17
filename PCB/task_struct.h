struct task_struct {
	//进程状态（-1就绪态，0运行态，>0停止态）
	volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	
	//进程内核栈
	void *stack;
	
	//有几个进程只在使用此结构
	atomic_t usage;
	
	//标记
	unsigned int flags;	/* per process flags, defined below */
	
	//ptrace系统调用，关于实现断点调试，跟踪进程运行。
	unsigned int ptrace;

	//锁的深度
	int lock_depth;		/* BKL lock depth */

	//SMP实现无加锁的进程切换
#ifdef CONFIG_SMP
#ifdef __ARCH_WANT_UNLOCKED_CTXSW
	int oncpu;
#endif
#endif

	//关于进程调度
	int prio, static_prio, normal_prio;
	
	//优先级
	unsigned int rt_priority;
	
	//关于进程
	const struct sched_class *sched_class;
	struct sched_entity se;
	struct sched_rt_entity rt;

	//preempt_notifier结构体链表
#ifdef CONFIG_PREEMPT_NOTIFIERS
	/* list of struct preempt_notifier: */
	struct hlist_head preempt_notifiers;
#endif

	/*
	 * fpu_counter contains the number of consecutive context switches
	 * that the FPU is used. If this is over a threshold, the lazy fpu
	 * saving becomes unlazy to save the trap. This is an unsigned char
	 * so that after 256 times the counter wraps and the behavior turns
	 * lazy again; this to deal with bursty apps that only use FPU for
	 * a short time
	 */
	 
	 //FPU使用计数
	unsigned char fpu_counter;
	
	//块设备I/O层的跟踪工具
#ifdef CONFIG_BLK_DEV_IO_TRACE
	unsigned int btrace_seq;
#endif
	//进程调度策略相关的字段
	unsigned int policy;
	
	cpumask_t cpus_allowed;

	//RCU同步原语
#ifdef CONFIG_TREE_PREEMPT_RCU
	int rcu_read_lock_nesting;
	char rcu_read_unlock_special;
	struct rcu_node *rcu_blocked_node;
	struct list_head rcu_node_entry;
#endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */

//用于调度器统计进程运行信息
#if defined(CONFIG_SCHEDSTATS) || defined(CONFIG_TASK_DELAY_ACCT)
	struct sched_info sched_info;
#endif

//用于构架进程链表
	struct list_head tasks;
	struct plist_node pushable_tasks;

	//关于进程的地址空间，指向进程的地址空间。（链表和红黑树）
	struct mm_struct *mm, *active_mm;

/* task state */
	//进程状态参数
	int exit_state;
	
	//退出信号处理
	int exit_code, exit_signal;
	
	//接收父进程终止的时候会发送信号
	int pdeath_signal;  /*  The signal sent when the parent dies  */
	/* ??? */
	unsigned int personality;
	unsigned did_exec:1;
	unsigned in_execve:1;	/* Tell the LSMs that the process is doing an
				 * execve */
	unsigned in_iowait:1;


	/* Revert to default priority/policy when forking */
	unsigned sched_reset_on_fork:1;

	//进程pid，父进程ppid。
	pid_t pid;
	pid_t tgid;

	//防止内核堆栈溢出
#ifdef CONFIG_CC_STACKPROTECTOR
	/* Canary value for the -fstack-protector gcc feature */
	unsigned long stack_canary;
#endif

	/*
	 * pointers to (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with
	 * p->real_parent->pid)
	 */
	 
	 //这部分是用来进行维护进程之间的亲属关系的。
	 //初始化父进程
	struct task_struct *real_parent; /* real parent process */
	//接纳终止的进程
	struct task_struct *parent; /* recipient of SIGCHLD, wait4() reports */
	/*
	 * children/sibling forms the list of my natural children
	 */
	 //维护子进程链表
	struct list_head children;	/* list of my children */
	//兄弟进程链表
	struct list_head sibling;	/* linkage in my parent's children list */
	//线程组组长
	struct task_struct *group_leader;	/* threadgroup leader */

	/*
	 * ptraced is the list of tasks this task is using ptrace on.
	 * This includes both natural children and PTRACE_ATTACH targets.
	 * p->ptrace_entry is p's link on the p->parent->ptraced list.
	 */
	 
	 //ptrace，系统调用，关于断点调试。
	struct list_head ptraced;
	struct list_head ptrace_entry;

	//PID与PID散列表的联系
	/* PID/PID hash table linkage. */
	struct pid_link pids[PIDTYPE_MAX];
	
	//维护一个链表，里面有该进程所有的线程
	struct list_head thread_group;

	//do_fork()函数
	struct completion *vfork_done;		/* for vfork() */
	int __user *set_child_tid;		/* CLONE_CHILD_SETTID */
	int __user *clear_child_tid;		/* CLONE_CHILD_CLEARTID */

	//描述CPU时间的内容
	//utime是用户态下的执行时间
	//stime是内核态下的执行时间
	cputime_t utime, stime, utimescaled, stimescaled;
	cputime_t gtime;
	cputime_t prev_utime, prev_stime;
	
	//上下文切换计数
	unsigned long nvcsw, nivcsw; /* context switch counts */
	struct timespec start_time; 		/* monotonic time */
	struct timespec real_start_time;	/* boot based time */
/* mm fault and swap info: this can arguably be seen as either mm-specific or thread-specific */
	
	//缺页统计
	unsigned long min_flt, maj_flt;

	struct task_cputime cputime_expires;
	struct list_head cpu_timers[3];

/* process credentials */

//进程身份凭据
	const struct cred *real_cred;	/* objective and real subjective task
					 * credentials (COW) */
	const struct cred *cred;	/* effective (overridable) subjective task
					 * credentials (COW) */
	struct mutex cred_guard_mutex;	/* guard against foreign influences on
					 * credential calculations
					 * (notably. ptrace) */
	struct cred *replacement_session_keyring; /* for KEYCTL_SESSION_TO_PARENT */
	
	//去除路径以后的可执行文件名称，进程名
	char comm[TASK_COMM_LEN]; /* executable name excluding path
				     - access with [gs]et_task_comm (which lock
				       it with task_lock())
				     - initialized normally by setup_new_exec */
/* file system info */

	//文件系统信息
	int link_count, total_link_count;
#ifdef CONFIG_SYSVIPC
/* ipc stuff */
//进程通信
	struct sysv_sem sysvsem;
#endif
#ifdef CONFIG_DETECT_HUNG_TASK
/* hung task detection */
	unsigned long last_switch_count;
#endif

//该进程在特点CPU下的状态
/* CPU-specific state of this task */
	struct thread_struct thread;
	
	//文件系统信息结构体
/* filesystem information */
	struct fs_struct *fs;
	
	//打开文件相关信息结构体
/* open file information */
	struct files_struct *files;
/* namespaces */
//命名空间：
	struct nsproxy *nsproxy;
/* signal handlers */

	//关于进行信号处理
	struct signal_struct *signal;
	struct sighand_struct *sighand;

	sigset_t blocked, real_blocked;
	sigset_t saved_sigmask;	/* restored if set_restore_sigmask() was used */
	struct sigpending pending;

	unsigned long sas_ss_sp;
	size_t sas_ss_size;
	int (*notifier)(void *priv);
	void *notifier_data;
	sigset_t *notifier_mask;
	
	//进程审计
	struct audit_context *audit_context;
#ifdef CONFIG_AUDITSYSCALL
	uid_t loginuid;
	unsigned int sessionid;
#endif
	seccomp_t seccomp;

	
#ifdef CONFIG_UTRACE
	struct utrace *utrace;
	unsigned long utrace_flags;
#endif

//线程跟踪组
/* Thread group tracking */
   	u32 parent_exec_id;
   	u32 self_exec_id;
/* Protection of (de-)allocation: mm, files, fs, tty, keyrings, mems_allowed,
 * mempolicy */
	spinlock_t alloc_lock;

	//中断
#ifdef CONFIG_GENERIC_HARDIRQS
	/* IRQ handler threads */
	struct irqaction *irqaction;
#endif

//task_rq_lock函数所使用的锁
	/* Protection of the PI data structures: */
	spinlock_t pi_lock;

	//基于PI协议的等待互斥锁
#ifdef CONFIG_RT_MUTEXES
	/* PI waiters blocked on a rt_mutex held by this task */
	struct plist_head pi_waiters;
	/* Deadlock detection and priority inheritance handling */
	struct rt_mutex_waiter *pi_blocked_on;
#endif

//死锁检测
#ifdef CONFIG_DEBUG_MUTEXES
	/* mutex deadlock detection */
	struct mutex_waiter *blocked_on;
#endif

//中断
#ifdef CONFIG_TRACE_IRQFLAGS
	unsigned int irq_events;
	int hardirqs_enabled;
	unsigned long hardirq_enable_ip;
	unsigned int hardirq_enable_event;
	unsigned long hardirq_disable_ip;
	unsigned int hardirq_disable_event;
	int softirqs_enabled;
	unsigned long softirq_disable_ip;
	unsigned int softirq_disable_event;
	unsigned long softirq_enable_ip;
	unsigned int softirq_enable_event;
	int hardirq_context;
	int softirq_context;
#endif

//lockdep
#ifdef CONFIG_LOCKDEP
# define MAX_LOCK_DEPTH 48UL
	u64 curr_chain_key;
	int lockdep_depth;
	unsigned int lockdep_recursion;
	struct held_lock held_locks[MAX_LOCK_DEPTH];
	gfp_t lockdep_reclaim_gfp;
#endif

//日志文件
/* journalling filesystem info */

	void *journal_info;

/* stacked block device info */
	//块设备链表
	struct bio *bio_list, **bio_tail;

/* VM state */
	//虚拟内存状态，内存回收
	struct reclaim_state *reclaim_state;

	//存放块设备I/O流量信息
	struct backing_dev_info *backing_dev_info;

	//I/O调度器所用信息
	struct io_context *io_context;

	unsigned long ptrace_message;
	siginfo_t *last_siginfo; /* For ptrace use.  */
	
	//记录进程I/O计数
	struct task_io_accounting ioac;
#if defined(CONFIG_TASK_XACCT)
	u64 acct_rss_mem1;	/* accumulated rss usage */
	u64 acct_vm_mem1;	/* accumulated virtual memory usage */
	cputime_t acct_timexpd;	/* stime + utime since last update */
#endif

	//CPUSET功能
#ifdef CONFIG_CPUSETS
	nodemask_t mems_allowed;	/* Protected by alloc_lock */
#ifndef __GENKSYMS__
	/*
	 * This does not change the size of the struct_task(2+2+4=4+4)
	 * so the offsets of the remaining fields are unchanged and 
	 * therefore the kABI is preserved.  Only the kernel uses
	 * cpuset_mem_spread_rotor and cpuset_slab_spread_rotor so
	 * it is safe to change it to use shorts instead of ints.
	 */   
	unsigned short cpuset_mem_spread_rotor;
	unsigned short cpuset_slab_spread_rotor;
	int mems_allowed_change_disable;
#else
	int cpuset_mem_spread_rotor;
	int cpuset_slab_spread_rotor;
#endif
#endif

//Control Groups
#ifdef CONFIG_CGROUPS
	/* Control Group info protected by css_set_lock */
	struct css_set *cgroups;
	/* cg_list protected by css_set_lock and tsk->alloc_lock */
	struct list_head cg_list;
#endif

//futex同步机制
#ifdef CONFIG_FUTEX
	struct robust_list_head __user *robust_list;
#ifdef CONFIG_COMPAT
	struct compat_robust_list_head __user *compat_robust_list;
#endif
	struct list_head pi_state_list;
	struct futex_pi_state *pi_state_cache;
#endif

//关于内存检测工具Performance Event
#ifdef CONFIG_PERF_EVENTS
#ifndef __GENKSYMS__
	void * __reserved_perf__;
#else
	struct perf_event_context *perf_event_ctxp;
#endif
	struct mutex perf_event_mutex;
	struct list_head perf_event_list;
#endif

	//非一致内存访问
#ifdef CONFIG_NUMA
	struct mempolicy *mempolicy;	/* Protected by alloc_lock */
	short il_next;
#endif

	//文件系统互斥资源
	atomic_t fs_excl;	/* holding fs exclusive resources */
	
	//RCU链表
	struct rcu_head rcu;

	/*
	 * cache last used pipe for splice
	 */
	 
	 //管道
	struct pipe_inode_info *splice_pipe;
	
	//延迟计数
#ifdef	CONFIG_TASK_DELAY_ACCT
	struct task_delay_info *delays;
#endif
#ifdef CONFIG_FAULT_INJECTION
	int make_it_fail;
#endif
	struct prop_local_single dirties;
#ifdef CONFIG_LATENCYTOP
	int latency_record_count;
	struct latency_record latency_record[LT_SAVECOUNT];
#endif
	/*
	 * time slack values; these are used to round up poll() and
	 * select() etc timeout values. These are in nanoseconds.
	 */
	 
	 //time slack values,常用于poll和select函数
	unsigned long timer_slack_ns;
	unsigned long default_timer_slack_ns;

	//socket控制消息
	struct list_head	*scm_work_list;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	
	//ftrace跟踪器
	/* Index of current stored adress in ret_stack */
	int curr_ret_stack;
	/* Stack of return addresses for return function tracing */
	struct ftrace_ret_stack	*ret_stack;
	/* time stamp for last schedule */
	unsigned long long ftrace_timestamp;
	/*
	 * Number of functions that haven't been traced
	 * because of depth overrun.
	 */
	atomic_t trace_overrun;
	/* Pause for the tracing */
	atomic_t tracing_graph_pause;
#endif
#ifdef CONFIG_TRACING
	/* state flags for use by tracers */
	unsigned long trace;
	/* bitmask of trace recursion */
	unsigned long trace_recursion;
#endif /* CONFIG_TRACING */
	/* reserved for Red Hat */
	unsigned long rh_reserved[2];
#ifndef __GENKSYMS__
	struct perf_event_context *perf_event_ctxp[perf_nr_task_contexts];
#ifdef CONFIG_CGROUP_MEM_RES_CTLR /* memcg uses this to do batch job */
	struct memcg_batch_info {
		int do_batch;	/* incremented when batch uncharge started */
		struct mem_cgroup *memcg; /* target memcg of uncharge */
		unsigned long bytes; 		/* uncharged usage */
		unsigned long memsw_bytes; /* uncharged mem+swap usage */
	} memcg_batch;
#endif
#endif
};
