package xtc.lang.blink;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import xtc.lang.blink.EventLoop.ReplyHandler;
import xtc.lang.blink.Event.BlinkEventSource;
import xtc.lang.blink.Event.Java2NativeCompletionEvent;
import xtc.lang.blink.Event.DeathEvent;
import xtc.lang.blink.Event.RawTextMessageEvent;

/**
 * Event utility classes.
 */
public class EventUtil {

  /** A base class for composing the event reply handlers. */
  static abstract class CompositionalReplyHandler extends ReplyHandler {

    /** The list of the handlers. The ordering of this handler matters.*/
    protected final ReplyHandler[] handlers;

    /** Constructor. */
    CompositionalReplyHandler(ReplyHandler[] handlers) {
      this.handlers = handlers;
      assert handlers != null && handlers.length > 0;
    }
  }

  static final class EventReplyHandler extends ReplyHandler {
    static final class EventFilter{
      private BlinkEventSource source;
      private Class<?> eventClass;
      public EventFilter(BlinkEventSource source, Class<?> eventClass) {
        this.eventClass = eventClass;
        this.source = source;
      }
      public boolean matches(Event event) {
        return this.source == event.getSource() && eventClass.isInstance(event);
      }
    }

    private final EventFilter[] eventFilters;

    /**
     * @param eventClasses
     */
    public EventReplyHandler(EventFilter[] filters) {
      assert filters != null;
      this.eventFilters = filters;
    }
    boolean dispatch(Event e) {
      for(EventFilter f: eventFilters) {
        if (f.matches(e)) {
          setResult(e);
          return true;
        }
      }
      return false;
    }
    Event getEvent() {
      return (Event)getResult();
    }
  }

  /** Conjunctive Composition of the multiple reply handlers.*/
  static final class ConjunctiveReplyHandler extends CompositionalReplyHandler {
    
    ConjunctiveReplyHandler(ReplyHandler[] handlers) {
      super(handlers);
    }
    
    /** Convenience constructors */    
    ConjunctiveReplyHandler(ReplyHandler r1, ReplyHandler r2) {
      this(new ReplyHandler[] {r1, r2});
    }
    ConjunctiveReplyHandler(ReplyHandler r1, ReplyHandler r2, ReplyHandler r3) {
      this(new ReplyHandler[] {r1, r2, r3});
    }

    /** The dispatch implementation. */
    boolean dispatch(Event e) {
      if (getResult() != null) {return true;}
      int numSatisfied = 0;
      Object result = null;
      for(final ReplyHandler h : handlers) {
        if (h.dispatch(e)) {
          result = h.getResult();
          numSatisfied++;
        }
      }      
      if (numSatisfied == handlers.length) {
        assert result != null;
        setResult(result);
        return true;
      } else {
        return false;  
      }
    }
  }

  static abstract class SingleSourceReplyHandler extends ReplyHandler {
    /** The event source to keep track of. */
    protected final BlinkEventSource sourceFilter;

    public SingleSourceReplyHandler(final BlinkEventSource sourceFilter) {
      this.sourceFilter = sourceFilter;
    }

    public BlinkEventSource getSourceFilter() {
      return sourceFilter;
    }
  }


  /** A Declarative reply handler using regular expression. */
  static final class RegExpReplyHandler extends SingleSourceReplyHandler {

    /** The specification - regular expression.*/
    private final Pattern p;

    /** The message accumulated for all the dispatch method calls. */
    private final StringBuffer buf;

    /** The pattern matter. */
    private final Matcher m;
    
    /**
     * @param sourceFilter The event source filter.
     * @param regex The regular expression.
     */
    RegExpReplyHandler(BlinkEventSource sourceFilter, String regex) {
      super(sourceFilter);
      this.p = Pattern.compile(regex);
      this.buf = new StringBuffer();
      this.m = p.matcher(buf);
    }

    /** 
     * Dispatch the debugger's message event.
     * @param e The event.
     * @return true the regular expression is found
     */
    boolean dispatch(Event e) {
      if (getResult() != null) {return true;}
      if (e.getSource() != sourceFilter ) {
        return false;
      } 
      if (e instanceof RawTextMessageEvent == false ) {
        return false;
      }
      RawTextMessageEvent me = (RawTextMessageEvent)e; 
      String msg = new String(me.getMessage());
      buf.append(msg);
      m.reset(buf);
      if (m.find()) {
        setResult(m);
        return true;
      } else {
        return false;
      }
    }

    /**
     * Getter method. 
     * @return The matcher.
     */
    public Matcher getMatcher() {
      return m;
    }
  }

  static abstract class EventClassReplyHandler extends SingleSourceReplyHandler {
    EventClassReplyHandler(BlinkEventSource sourceFilter) {
      super(sourceFilter);
    }
    public Event getEvent() {
      return (Event)getResult();
    }
  }
  /** Observe the end of the death of the event source. */
  static final class DeathReplyHandler extends EventClassReplyHandler {
    
    public DeathReplyHandler(BlinkEventSource sourceFilter) {
      super(sourceFilter);
    }
    boolean dispatch(Event e) {
      if (getResult() != null) {return true;}
      if (e instanceof DeathEvent 
          && e.getSource() == sourceFilter) {
        setResult(e);
        return true;
      }
      return false;
    }
  }

  static final class J2CCompletionEventHandler extends EventClassReplyHandler {

    public J2CCompletionEventHandler(JavaDebugger sourceFilter) {
      super(sourceFilter);
    }

    boolean dispatch(Event e) {
      if (getResult() != null) {return true;}
      if (e instanceof Java2NativeCompletionEvent 
          && e.getSource() == sourceFilter) {
        setResult(e);
        return true;
      }
      return false;
    }    
  }
}
