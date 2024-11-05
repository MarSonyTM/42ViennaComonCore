'use client';

import React, { useState, useEffect } from 'react';
import { format, startOfWeek, addDays } from 'date-fns';

interface TimeSlot {
  id: string;
  time: string;
  available: boolean;
}

interface WeekDay {
  date: Date;
  label: string;
}

export default function WeeklySchedule() {
  const [selectedDate, setSelectedDate] = useState<Date>(new Date());
  const [timeSlots, setTimeSlots] = useState<TimeSlot[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(true);
  
  // Generate week days (Monday to Friday)
  const weekStart = startOfWeek(selectedDate, { weekStartsOn: 1 });
  const weekDays: WeekDay[] = Array.from({ length: 5 }).map((_, index) => {
    const date = addDays(weekStart, index);
    return {
      date,
      label: format(date, 'EEE dd/MM')
    };
  });

  // Generate time slots with client-side only availability
  useEffect(() => {
    setIsLoading(true);
    const slots: TimeSlot[] = Array.from({ length: 14 }).map((_, index) => {
      const hour = Math.floor(index / 2) + 9; // Start at 9 AM
      const minute = (index % 2) * 30;
      return {
        id: `slot-${index}`,
        time: `${hour.toString().padStart(2, '0')}:${minute.toString().padStart(2, '0')}`,
        available: true, // Default to available, will be updated with real data later
      };
    });
    setTimeSlots(slots);
    setIsLoading(false);
  }, [selectedDate]);

  if (isLoading) {
    return (
      <div className="flex justify-center items-center py-8">
        <div className="text-gray-600">Loading schedule...</div>
      </div>
    );
  }

  return (
    <div className="max-w-6xl mx-auto p-4">
      <div className="mb-6 flex justify-between items-center">
        <button 
          className="bg-gray-100 hover:bg-gray-200 px-4 py-2 rounded transition-colors"
          onClick={() => setSelectedDate(addDays(selectedDate, -7))}
        >
          Previous Week
        </button>
        <h2 className="text-xl font-semibold">
          Week of {format(weekStart, 'MMMM d, yyyy')}
        </h2>
        <button 
          className="bg-gray-100 hover:bg-gray-200 px-4 py-2 rounded transition-colors"
          onClick={() => setSelectedDate(addDays(selectedDate, 7))}
        >
          Next Week
        </button>
      </div>

      <div className="overflow-x-auto">
        <div className="grid grid-cols-6 gap-2 min-w-[800px]">
          <div className="col-span-1"></div>
          {weekDays.map(({ label }) => (
            <div key={label} className="text-center font-semibold">
              {label}
            </div>
          ))}
          
          {timeSlots.map((slot) => (
            <React.Fragment key={slot.id}>
              <div className="text-right pr-2 text-sm">
                {slot.time}
              </div>
              {weekDays.map(({ date, label }) => (
                <button
                  key={`${label}-${slot.id}`}
                  className={`p-2 rounded transition-colors ${
                    slot.available 
                      ? 'bg-green-100 hover:bg-green-200 cursor-pointer' 
                      : 'bg-gray-100 cursor-not-allowed'
                  }`}
                  onClick={() => {
                    if (slot.available) {
                      alert(`Booking slot for ${format(date, 'dd/MM')} at ${slot.time}`);
                    }
                  }}
                  disabled={!slot.available}
                >
                  {slot.available ? 'Available' : 'Booked'}
                </button>
              ))}
            </React.Fragment>
          ))}
        </div>
      </div>
    </div>
  );
} 